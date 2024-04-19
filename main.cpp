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

#include <FlexCAN.h>
#include "CANDriver.h"
#include <cstdint>
#include "Config.h"
#include "LEDController.h"


int alara = ALARA_ID;
File onBoardLog;
char* fileLogName = "SoftwareTest-04-15-2024.txt";
bool sd_write = true;
Rocket myRocket = Rocket(alara);
LEDController allOfTheLights;

const int CAN2busSpeed = 125000;
CANDriver theSchoolBus = CANDriver();

uint32_t lastPing; 
uint32_t lastPingRecieved;         
uint32_t lastCANReport;     
bool calibratedPTs; 
ADC* adc = new ADC();
ADC_REFERENCE ref0 = ADC_REFERENCE::REF_1V2;
ADC_REFERENCE ref1 = ADC_REFERENCE::REF_1V2;
// Global variable initialize

// These need to not have a value or the value will be set to that throughout the duration of the program. Initialize in setup().
uint32_t ignitionTime;
uint32_t LMVOpenTime;
uint32_t FMVOpenTime;
uint32_t LMVCloseTime;
uint32_t FMVCloseTime;


//4/16: Trying this again.
// 4/14 Ensure that these are initialized as 0.
uint32_t zeroPTOne=0;
uint32_t zeroPTTwo=0;
uint32_t zeroPTThree=0;
uint32_t zeroPTFour=0;
uint32_t zeroPTFive=0;
uint32_t zeroPTSix=0;
uint32_t zeroPTSeven=0;
uint32_t zeroPTEight=0;
float calibVal;
bool calibIsM;
uint8_t sensorCalibID;
std::vector <uint32_t> PTZeros{zeroPTOne, zeroPTTwo, zeroPTThree, zeroPTFour, zeroPTFive, zeroPTSix, zeroPTSeven, zeroPTEight};


std::vector<Color> firstLED{GREEN,  PURPLE, RED, ORANGE, ORANGE, WHITE, ORANGE, GREEN};
std::vector<Color> secondLED{PURPLE, PURPLE, RED, GREEN,  BLUE,   WHITE, ORANGE, GREEN};

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


void executeCommand(uint32_t commandID);
std::string generateSDReport();
void CANroutine(char*);
void fireRoutine();
void executeCommand(uint32_t);
void MCUADCSetup(ADC&, ADC_REFERENCE, ADC_REFERENCE, uint8_t, uint8_t);
void safetyChecks();


void writeSDReport(char* fileLogName) {
    if (sd_write)
    {   
        File onBoardLog = SD.open(fileLogName, FILE_WRITE);   
        char entry[300];
        snprintf(entry, sizeof(entry), " | State %d", myRocket.getState());
        
        int i = 0;
        for (std::map<int,Sensor>::iterator sensor = myRocket.sensorMap.begin(); sensor != myRocket.sensorMap.end(); ++sensor) 
        {
            snprintf(entry + strlen(entry), sizeof(entry) - strlen(entry), " | S %d: %f", sensor->first, myRocket.sensorRead(sensor->first, *adc));
        }
        for (std::map<int,Valve>::iterator valve = myRocket.valveMap.begin(); valve != myRocket.valveMap.end(); ++valve) 
        {
            snprintf(entry + strlen(entry), sizeof(entry) - strlen(entry), " | V %d: %d", valve->first, myRocket.valveRead(valve->first));
        }
        for (std::map<int,Igniter>::iterator igniter = myRocket.igniterMap.begin(); igniter != myRocket.igniterMap.end(); ++igniter) 
        {
            snprintf(entry + strlen(entry), sizeof(entry) - strlen(entry), " | I %d: %d", igniter->first, myRocket.ignitionRead(igniter->first));
        }
        onBoardLog.printf("Time (ms) : %d %s \n", millis(), entry);
    }
}

void CANRoutine(uint32_t time) {                
     // 4/14: Changed to uint32_t
    uint32_t msgID;
    if (time - lastCANReport > CAN_INTERVAL) {
        msgID = SENS_1_4_PROP;
        if (alara == 0) msgID = SENS_9_12_ENGINE;
        int sensorReads[8] = {0};
        int i = 0;
        for (std::map<int,Sensor>::iterator sensor = myRocket.sensorMap.begin(); sensor != myRocket.sensorMap.end(); ++sensor) {
            sensorReads[i++] = myRocket.sensorRead(sensor->first, *adc);
        }


        // Don't forget to include this in the PT zeroing section as well.VVV
        theSchoolBus.sendSensorData(msgID,sensorReads[0]-zeroPTOne, sensorReads[1]-zeroPTTwo, 
                                    sensorReads[2]-zeroPTThree, sensorReads[3]-zeroPTFour);
        theSchoolBus.sendSensorData(msgID+1,sensorReads[4]-zeroPTFive, sensorReads[5]-zeroPTSix, 
                                    sensorReads[6]-zeroPTSeven, sensorReads[7]-zeroPTEight);
        theSchoolBus.sendStateReport(millis(), myRocket.getState(), myRocket, alara);
        lastCANReport = time;
    }

    return;
}

void fireRoutine() {        //  4/14: Changed to uint32_t from int.
    uint32_t curMillis = millis(); 
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
        //executeCommand(theSchoolBus.readMessage());
        CANRoutine(millis());
        writeSDReport(fileLogName);
    }
}

void executeCommand(uint32_t commandID) {   
    if (myRocket.getManualVent() || commandID == MANUAL_OVERRIDE) {
        int* it = std::find(std::begin(manualVentCommandIds), std::end(manualVentCommandIds), commandID);
        if (it != std::end(manualVentCommandIds)) myRocket.setValveOn(commandID / 2, commandID % 2);
        if (commandID == MANUAL_OVERRIDE) {
            myRocket.setManualVent(!myRocket.getManualVent());
            Serial.printf("returning %d", myRocket.getManualVent());
            if (!myRocket.getManualVent()) myRocket.changeState(myRocket.getState());
        }
        return;
    }
    if (commandID <= TEST && state_transitions[myRocket.getState()][commandID]) {
        myRocket.changeState(commandID);
        allOfTheLights.setLed(LED0, firstLED[commandID]);
        allOfTheLights.setLed(LED1, secondLED[commandID]);
        if (commandID == FIRE) fireRoutine();
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
    if (commandID == PING_PI_ROCKET) {
        lastPingRecieved = millis();
        theSchoolBus.ping(alara);
    }
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
  adc.adc0->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED_16BITS); // change the conversion speed
  adc.adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED);     // change the sampling speed
  adc.adc0->recalibrate();

///// ADC1 /////
  adc.adc1->setReference(refIn1);
  adc.adc1->setAveraging(averagesIn1);                                    // set number of averages
  adc.adc1->setResolution(16);                                   // set bits of resolution
  adc.adc1->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED_16BITS); // change the conversion speed
  adc.adc1->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED);     // change the sampling speed
  adc.adc1->recalibrate();

}

void safetyChecks() 
{   // Lox pressure reading (?)
    // This will be longer than two minutes.
    if(lastPing > 600000) 
        myRocket.changeState(VENT);
}

void setup() {
    
    Serial.begin(9600);
    Serial.println("Serial Test");
    Wire.begin();
    SPI.begin();
    
    if (!SD.begin(BUILTIN_SDCARD)) {
        sd_write = false;
    }
    
    myRocket = Rocket(alara);
    allOfTheLights.init();
    ADC* adc = new ADC();


    Can0.begin(CAN2busSpeed);
    Can0.setTxBufferSize(64);

    lastPing = 0;


    // Do we want default values?
    ignitionTime = 0;
    LMVOpenTime = 1000;
    FMVOpenTime = 2000;
    LMVCloseTime = 3000;
    FMVCloseTime = 4000;


    calibratedPTs = true;

    ADC_REFERENCE ref0 = ADC_REFERENCE::REF_1V2;
    ADC_REFERENCE ref1 = ADC_REFERENCE::REF_1V2;
    uint8_t averages0 = 4;
    uint8_t averages1 = 4;
    MCUADCSetup(*adc, ref0, ref1, averages0, averages1);
}

void loop() {
    lastPing = millis() - lastPingRecieved;
    executeCommand(theSchoolBus.readMessage());
    CANRoutine(millis());
    writeSDReport(fileLogName);
    safetyChecks();
}