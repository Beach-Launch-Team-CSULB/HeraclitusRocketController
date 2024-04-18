#include "Arduino.h"
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

const int CAN2busSpeed = 500000;
CANDriver theSchoolBus = CANDriver();

uint32_t lastPing; 
uint32_t lastPingRecieved;         
uint32_t lastCANReport;     
bool calibratedPTs; 
// Global variable initialize

// These need to not have a value or the value will be set to that throughout the duration of the program. Initialize in setup().
uint32_t ignitionTime;
uint32_t LMVOpenTime;
uint32_t FMVOpenTime;
uint32_t LMVCloseTime;
uint32_t FMVCloseTime;


//4/16: Trying this again.
// 4/14 Ensure that these are initialized as 0.
uint32_t zeroPTOne;
uint32_t zeroPTTwo;
uint32_t zeroPTThree;
uint32_t zeroPTFour;
uint32_t zeroPTFive;
uint32_t zeroPTSix;
uint32_t zeroPTSeven;
uint32_t zeroPTEight;
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

std::string generateSDReport() {
    std::string entry = std::to_string(millis());
    entry = entry + " | State: " + std::to_string(myRocket.getState());

    for (std::map<int,Sensor>::iterator sensor = myRocket.sensorMap.begin(); sensor != myRocket.sensorMap.end(); ++sensor) {
        entry = entry + " | " + std::to_string(sensor->first) + ":" + std::to_string(myRocket.sensorRead(sensor->first));
    }
    for (std::map<int,Valve>::iterator valve = myRocket.valveMap.begin(); valve != myRocket.valveMap.end(); ++valve) {
        entry = entry + " | " + std::to_string(valve->first) + ":" + std::to_string(myRocket.valveRead(valve->first));
    }
    for (std::map<int,Igniter>::iterator igniter = myRocket.igniterMap.begin(); igniter != myRocket.igniterMap.end(); ++igniter) {
        entry = entry + " | " + std::to_string(igniter->first) + ":" + std::to_string(myRocket.ignitionRead(igniter->first));
    }

    return entry + '\n';
}

void writeSDReport(char* fileLogName) {
    if (sd_write)
    {   
        File onBoardLog = SD.open(fileLogName, FILE_WRITE);   
        char entry[300];
        //entry = entry + " | State: %d" + std::to_string(myRocket.getState());
        snprintf(entry, sizeof(entry), " | State %d", myRocket.getState());
        
        int i = 0;
        for (std::map<int,Sensor>::iterator sensor = myRocket.sensorMap.begin(); sensor != myRocket.sensorMap.end(); ++sensor) 
        {
            // 4/14: Added to this. Had to create a vector of initial PT Values.
            //entry = entry + " | " + std::to_string(sensor->first) + ":" + std::to_string(myRocket.sensorRead(sensor->first) - PTZeros[i]);
            //entry = entry + " | " + std::to_string(sensor->first) + ":" + std::to_string(myRocket.sensorRead(sensor->first));
            snprintf(entry + strlen(entry), sizeof(entry) - strlen(entry), " | S %d: %f", sensor->first, myRocket.sensorRead(sensor->first));
        }
        for (std::map<int,Valve>::iterator valve = myRocket.valveMap.begin(); valve != myRocket.valveMap.end(); ++valve) 
        {
            snprintf(entry + strlen(entry), sizeof(entry) - strlen(entry), " | V %d: %d", valve->first, myRocket.valveRead(valve->first));

            //entry = entry + " | " + std::to_string(valve->first) + ":" + std::to_string(myRocket.valveRead(valve->first));
        }
        for (std::map<int,Igniter>::iterator igniter = myRocket.igniterMap.begin(); igniter != myRocket.igniterMap.end(); ++igniter) 
        {
            snprintf(entry + strlen(entry), sizeof(entry) - strlen(entry), " | I %d: %d", igniter->first, myRocket.ignitionRead(igniter->first));

            //entry = entry + " | " + std::to_string(igniter->first) + ":" + std::to_string(myRocket.ignitionRead(igniter->first));
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
            sensorReads[i++] = myRocket.sensorRead(sensor->first);
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

void fireRoutine(uint32_t zeroTime) {        //  4/14: Changed to uint32_t from int.
    uint32_t curMillis = zeroTime;           //  4/14: Changed to uint32_t from int.
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
        //executeCommand(theSchoolBus.readMessage());
        CANRoutine(millis());
        writeSDReport(fileLogName);
    }
    // 4/14: Do we need these things here? ********************


}


void fireRoutineSetup() 
{
    uint32_t time = millis(); 
    Serial.printf("%d, %d, %d, %d", LMVOpenTime, LMVCloseTime, FMVOpenTime, FMVCloseTime);      
    // 4/14: Changed to uint32_t from int.
    return fireRoutine(time);
}



void executeCommand(uint32_t commandID) {   

    if (commandID <= TEST && state_transitions[myRocket.getState()][commandID]) {
        myRocket.changeState(commandID);
        allOfTheLights.setLed(LED0, firstLED[commandID]);
        allOfTheLights.setLed(LED1, secondLED[commandID]);
        if (commandID == FIRE) fireRoutineSetup();
    }

    else if (myRocket.getState() == TEST && commandID <= FMV_OPEN) 
    {
        if (commandID <= IGN2_ON) 
            myRocket.setIgnitionOn(commandID / 2, commandID % 2);
        else if (commandID <= FMV_OPEN) 
            myRocket.setValveOn(commandID / 2, commandID % 2);
    }
    else if (commandID == PING_PI_ROCKET) {
        lastPingRecieved = millis();
        theSchoolBus.ping(alara);
    }
    else if (commandID == ZERO_PTS)
    {
        if(calibratedPTs == true)
        {
            myRocket.calibrateSensors(alara);
            calibratedPTs = false; 
        }
        else
        {
            // Go fish.
        }
    }
    else if (commandID == GET_LMV_OPEN)
        theSchoolBus.sendTiming(SEND_LMV_OPEN);
    else if (commandID == GET_FMV_OPEN)
        theSchoolBus.sendTiming(SEND_FMV_OPEN);
    else if (commandID == GET_LMV_CLOSE)
        theSchoolBus.sendTiming(SEND_LMV_CLOSE);
    else if (commandID == GET_FMV_CLOSE)
        theSchoolBus.sendTiming(SEND_FMV_CLOSE);
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

    Can0.begin(CAN2busSpeed);
    Can0.setTxBufferSize(64);

    lastPing = 0;


    // Do we want default values?
    ignitionTime = 0;
    LMVOpenTime = 1000;
    FMVOpenTime = 2000;;
    LMVCloseTime = 3000;;
    FMVCloseTime = 4000;

    calibratedPTs = true;
}



void loop() {
    lastPing = millis() - lastPingRecieved;
    executeCommand(theSchoolBus.readMessage());
    CANRoutine(millis());
    writeSDReport(fileLogName);
    safetyChecks();
}
