#include "Arduino.h"
#include <Algorithm>
#include <iostream>
#include <array>
#include <unordered_map>
#include "Rocket.h"
#include "Igniter.h"
#include <unistd.h> 
//^ For sleep function
#include <SD.h>
#include <SPI.h>
#include "ExtendedIO.h"
#include <Wire.h>
#include <ADC.h>
#include <ADC_util.h>


#include <FlexCAN_T4.h>
#include "CANDriver.h"
#include <cstdint>
#include "Config.h"
#include "LEDController.h"


int alara = ALARA_ID;
File onBoardLog;
char* fileLogName = "SoftwareTest-04-15-2024.txt";
bool sd_write = false;
Rocket myRocket = Rocket(alara);
LEDController allOfTheLights;

const int CAN2busSpeed = 1000000;
CANDriver theSchoolBus = CANDriver();
FlexCAN_T4 Can0 = FlexCAN_T4<CAN1, RX_SIZE_16, TX_SIZE_16>();

uint32_t lastPing; 
uint32_t lastPingRecieved;         
uint32_t lastCANReport;     
bool calibratedPTs; 
ADC* adc = new ADC();
ADC_REFERENCE ref0 = ADC_REFERENCE::REF_3V3;
ADC_REFERENCE ref1 = ADC_REFERENCE::REF_3V3;
// Global variable initialize

// These need to not have a value or the value will be set to that throughout the duration of the program. Initialize in setup().
uint32_t ignitionTime;
uint32_t LMVOpenTime;
uint32_t FMVOpenTime;
uint32_t LMVCloseTime;
uint32_t FMVCloseTime;


float calibVal;
bool calibIsM;
uint8_t sensorCalibID;


int state_transitions[9][9] = {
    //                                          TO
    //                  ABORT, VENT, FIRE, TANK_PRESS, HIGH_PRESS, STANDBY,    IGNITE,   TEST, MANUAL_VENT
    /*      ABORT */     {0,    1,     0,       0,         0,         1,          0,       0,       0},
    /*      VENT */      {1,    0,     0,       0,         0,         1,          0,       0,       0}, 
    /* F    FIRE */      {1,    1,     0,       0,         0,         1,          0,       0,       0}, 
    /* R    TANK_PRESS */{1,    1,     0,       0,         0,         0,          1,       0,       1}, 
    /* O    HIGH_PRESS */{1,    1,     0,       1,         0,         0,          0,       0,       1}, 
    /* M    STANDBY */   {1,    1,     0,       0,         1,         0,          0,       1,       0}, 
    /*      IGNITE*/     {1,    1,     1,       0,         0,         0,          0,       0,       1}, 
    /*      TEST */      {1,    1,     0,       0,         0,         1,          0,       0,       0},
    /*      MANUAL_VENT*/{1,    1,     1,       1,         1,         0,          1,       0,       0}
};

int manualVentCommandIds[] = {12, 13, 16, 17, 18, 19, 24, 25, 26, 27};


void start_sd_log();
void executeCommand(uint32_t commandID);
std::string generateSDReport();
void CANroutine(char*);
void fireRoutine();
void executeCommand(uint32_t);
void MCUADCSetup(ADC&, ADC_REFERENCE, ADC_REFERENCE, uint8_t, uint8_t);
void safetyChecks();

void start_sd_log() {
    if (!SD.begin(BUILTIN_SDCARD)) {
        sd_write = false;
        return;
    }
    if (!sd_write) {
        File onBoardLog = SD.open(fileLogName, FILE_WRITE);   
        char entry[300] = "time,state,PT_LOX_HIGH,PT_FUEL_HIGH,PT_LOX_DOME,PT_FUEL_DOME,PT_LOX_1,PT_LOX_2,PT_FUEL_1,PT_FUEL_2,PT_PNEUMATICS,PT_LOX_IN,PT_FUEL_IN,PT_FUEL_INJ,PT_CHAMBER_1,PT_CHAMBER_2,HV,HP,LDV,FDV,LDR,FDR,LV,FV,LMV,FMV,IGN1,IGN2,";
        onBoardLog.printf("%s\n", entry);
    }
    sd_write = true;
}

void writeSDReport(char* fileLogName) { 
    if (sd_write)
    {   
        File onBoardLog = SD.open(fileLogName, FILE_WRITE);   
        char entry[300];
        snprintf(entry, sizeof(entry), "%d,", myRocket.getState());
        
        for (std::map<int,Sensor>::iterator sensor = myRocket.sensorMap.begin(); sensor != myRocket.sensorMap.end(); ++sensor) 
        {
            snprintf(entry + strlen(entry), sizeof(entry) - strlen(entry), "%f,", myRocket.sensorRead(sensor->first, *adc));
        }
        for (std::map<int,Valve>::iterator valve = myRocket.valveMap.begin(); valve != myRocket.valveMap.end(); ++valve) 
        {
            snprintf(entry + strlen(entry), sizeof(entry) - strlen(entry), "%d,", myRocket.valveRead(valve->first));
        }
        for (std::map<int,Igniter>::iterator igniter = myRocket.igniterMap.begin(); igniter != myRocket.igniterMap.end(); ++igniter) 
        {
            snprintf(entry + strlen(entry), sizeof(entry) - strlen(entry), "%d,", myRocket.ignitionRead(igniter->first));
        }
        onBoardLog.printf("%d,%s \n", millis(), entry);
    }
}

void CANRoutine(uint32_t time) {                
    // 4/14: Changed to uint32_t
    uint32_t msgID;
    if (time - lastCANReport > CAN_INTERVAL) {
        int sensorReads[16] = {0};
        int i = 0;
        msgID = SENS_1_4_PROP;
        for (std::map<int,Sensor>::iterator sensor = myRocket.sensorMap.begin(); sensor != myRocket.sensorMap.end(); ++sensor) {
            sensorReads[i++] = myRocket.sensorRead(sensor->first, *adc);
        }
        // Don't forget to include this in the PT zeroing section as well.VVV
        // node 1
        theSchoolBus.sendSensorData(msgID,sensorReads[0], sensorReads[1], 
                                    sensorReads[2], sensorReads[3]);
        theSchoolBus.sendSensorData(++msgID,sensorReads[4], sensorReads[5], 
                                    sensorReads[6], sensorReads[7]);
        theSchoolBus.sendStateReport(millis(), myRocket.getState(), myRocket, 1);

        // node 0
        theSchoolBus.sendSensorData(++msgID,sensorReads[8], sensorReads[9], 
                                    sensorReads[10], sensorReads[11]);
        theSchoolBus.sendSensorData(++msgID,sensorReads[12], sensorReads[13], sensorReads[14],sensorReads[15]);
        theSchoolBus.sendStateReport(millis(), myRocket.getState(), myRocket, 0);
        

        lastCANReport = time;
    }

    return;
}

void fireRoutine() {        //  4/14: Changed to uint32_t from int.
    uint32_t curMillis = 0; 
    uint32_t zeroTime = millis();           //  4/14: Changed to uint32_t from int.
    while(curMillis < 100'000) {
        curMillis = (millis() - zeroTime);
        if (curMillis > LMVCloseTime) {
            myRocket.setValveOn(LMV_ID, false);
        }
        else if (curMillis > LMVOpenTime) {
            myRocket.setValveOn(LMV_ID, true);
        }
        if (curMillis > FMVCloseTime) {
            myRocket.setValveOn(FMV_ID, false);
        }
        else if (curMillis > FMVOpenTime) {
            myRocket.setValveOn(FMV_ID, true);
        }
        if (curMillis > FMVCloseTime && curMillis > LMVCloseTime) {
            Serial.println("exit");
            return;
        }

        // 4/17: Uncommenting the executeCommand();
        CANRoutine(millis());
        executeCommand(theSchoolBus.readMessage());
        writeSDReport(fileLogName);
    }
}

void executeCommand(uint32_t commandID) {   
    if (commandID == PING_PI_ROCKET) {
        lastPingRecieved = millis();
        theSchoolBus.ping(alara);
    }
    else if (commandID <= TEST && state_transitions[myRocket.getState()][commandID] && myRocket.getManualVent() == false) {
        myRocket.changeState(commandID);
        allOfTheLights.setLed(commandID);
        if (commandID == FIRE) fireRoutine();
    }
    else if (myRocket.getManualVent() || commandID == MANUAL_OVERRIDE) {
        int* it = std::find(std::begin(manualVentCommandIds), std::end(manualVentCommandIds), commandID);
        if (it != std::end(manualVentCommandIds)) myRocket.setValveOn(commandID / 2, commandID % 2);
        if (commandID == MANUAL_OVERRIDE) {
            myRocket.setManualVent(!myRocket.getManualVent());
            Serial.printf("returning %d", myRocket.getManualVent());
            if (!myRocket.getManualVent()) myRocket.changeState(myRocket.getState());
        }
        return;
    }
    else if (myRocket.getState() == TEST && commandID <= FMV_OPEN) 
    {
        if (commandID <= IGN2_ON) 
            myRocket.setIgnitionOn(commandID / 2, commandID % 2);
        else if (commandID <= FMV_OPEN) 
            myRocket.setValveOn(commandID / 2, commandID % 2);
    }
    else if (commandID == ZERO_PTS)
    {
        if(calibratedPTs == true)
        {
            myRocket.zeroSensors(alara);
            calibratedPTs = false; 
        }
        else
        {
            // Go fish.
        }
    }
    else if (commandID == GET_B_VAL || commandID == GET_M_VAL) {
        theSchoolBus.sendSensorCalibration(calibIsM, sensorCalibID, myRocket.getSensorCalibration(sensorCalibID, calibIsM));
    }
    else if (commandID == SET_B_VAL || commandID == SET_M_VAL) {
        myRocket.calibrateSensor(sensorCalibID, calibIsM, calibVal);
    }
    else if (commandID == GET_LMV_OPEN)
        theSchoolBus.sendTiming(SEND_LMV_OPEN);
    else if (commandID == GET_FMV_OPEN)
        theSchoolBus.sendTiming(SEND_FMV_OPEN);
    else if (commandID == GET_LMV_CLOSE)
        theSchoolBus.sendTiming(SEND_LMV_CLOSE);
    else if (commandID == GET_FMV_CLOSE)
        theSchoolBus.sendTiming(SEND_FMV_CLOSE);
    else if (commandID == START_SD_LOG)
        start_sd_log();

}

void MCUADCSetup(ADC& adc, ADC_REFERENCE refIn0, ADC_REFERENCE refIn1, uint8_t averagesIn0, uint8_t averagesIn1)
{ 
//Ideally get some conditionals here for which MCU it is so this is compatible at least also with Teensy LC

///// ADC0 /////
  // reference can be ADC_REFERENCE::REF_3V3, ADC_REFERENCE::REF_1V2 or ADC_REFERENCE::REF_EXT.
  //adc->setReference(ADC_REFERENCE::REF_1V2, ADC_0); // change all 3.3 to 1.2 if you change the reference to 1V2

  adc.adc0->setReference(refIn0);
  adc.adc0->setAveraging(averagesIn0);                                    // set number of averages
  adc.adc0->setResolution(16);                                   // set bits of resolution
  adc.adc0->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED); // change the conversion speed
  adc.adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED);     // change the sampling speed
  adc.adc0->recalibrate();

///// ADC1 /////
  adc.adc1->setReference(refIn1);
  adc.adc1->setAveraging(averagesIn1);                                    // set number of averages
  adc.adc1->setResolution(16);                                   // set bits of resolution
  adc.adc1->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED); // change the conversion speed
  adc.adc1->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED);     // change the sampling speed
  adc.adc1->recalibrate();

}

void safetyChecks() 
{   // Lox pressure reading (?)
    // This will be longer than two minutes.
    if(lastPing > 600000) 
        myRocket.changeState(VENT);
}

int last_light;
void setup() {
    
    Serial.begin(9600);
    Serial.println("Serial Test");
    Wire.begin();
    SPI.begin();
    Can0.begin();
    start_sd_log();
    pinMode(33, OUTPUT);
    Can0.setBaudRate(CAN2busSpeed);
    
    myRocket = Rocket(alara);
    allOfTheLights = LEDController(LED_PIN_1, LED_PIN_2, LED_PIN_3);
    //allOfTheLights.setLed(0);

    //Can0.begin(CAN2busSpeed);
    //Can0.setTxBufferSize(64);

    lastPing = 0;
    last_light = millis();

    // Do we want default values?
    ignitionTime = 0;
    LMVOpenTime = 1000;
    FMVOpenTime = 2000;
    LMVCloseTime = 3000;
    FMVCloseTime = 4000;

    calibIsM = false;
    calibVal = 0.0;
    sensorCalibID = 0;


    calibratedPTs = true;

    ADC_REFERENCE ref0 = ADC_REFERENCE::REF_3V3;
    ADC_REFERENCE ref1 = ADC_REFERENCE::REF_3V3;
    uint8_t averages0 = 4;
    uint8_t averages1 = 4;
    MCUADCSetup(*adc, ref0, ref1, averages0, averages1);

    }
int i = 0;
void loop() {
    while(true) {
        allOfTheLights.setLed(++i%8);
        delay(1000);
     
    static CAN_message_t msg;
    msg.id = 100;
    Can0.write(msg);
    //lastPing = millis() - lastPingRecieved;
    //executeCommand(theSchoolBus.readMessage());
    //CANRoutine(millis());
    writeSDReport(fileLogName);
    //safetyChecks();*/
    }
}