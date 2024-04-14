#include "Arduino.h"
#include <iostream>
#include <array>
#include <unordered_map>
#include "Rocket.h"
#include "Igniter.h"
#include <unistd.h> // For sleep function
#include <SD.h>
#include <SPI.h>
#include "ExtendedIO.h"
#include <Wire.h>

#include <FlexCAN.h>
#include "CANDriver.h"
#include <cstdint>
#include "Config.h"

// These need to not have a value or the value will be set to that throughout the duration of the program.
// Initialize in setup()
uint32_t ignitionTime;
uint32_t LMVOpenTime;
uint32_t FMVOpenTime;
uint32_t LMVCloseTime;
uint32_t FMVCloseTime;

int alara = ALARA_ID;
File onBoardLog;
char* fileLogName = "SoftwareTest-03-15-2024.txt";
bool sd_write = true;
Rocket myRocket = Rocket(alara);

bool calibratedPTs; // Global variable initialized as zero.

const int CAN2busSpeed = 500000;

// "test" has been renamed theSchoolBus
CANDriver theSchoolBus = CANDriver();

int lastPing;
int lastCANReport;


//uint32_t verifier;


// 4/12: I was unable to go to standy from Vent and Abort, and I was only able to go from Passive from Vent.

// 4/13: 
int state_transitions[9][9] = {
    //                                          TO
    //                  ABORT, VENT, FIRE, TANK_PRESS, HIGH_PRESS, STANDBY,    IGNITE,   TEST, MANUAL_VENT
    /*      ABORT */     {0,    1,     0,       0,         0,         1,          0,       0,       0},
    /*      VENT */      {1,    0,     0,       0,         0,         1,          0,       0,       0}, 
    /* F    FIRE */      {1,    1,     0,       0,         0,         1,          0,       0,       0}, 
    /* R    TANK_PRESS */{1,    1,     0,       0,         0,         0,          1,       0,       1}, 
    /* O    HIGH_PRESS */{1,    1,     0,       1,         0,         0,          0,       0,       1}, 
    /* M    STANDBY */   {1,    1,     0,       0,         0,         0,          0,       1,       0}, 
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

void CANRoutine(int time) {
    uint32_t msgID = 255;
    if (time - lastCANReport > CAN_INTERVAL) {
        msgID = SENS_1_4_PROP;
        if (alara == 0) msgID = SENS_9_12_ENGINE;
        int sensorReads[8] = {0};
        int i = 0;
        for (std::map<int,Sensor>::iterator sensor = myRocket.sensorMap.begin(); sensor != myRocket.sensorMap.end(); ++sensor) {
            sensorReads[i++] = myRocket.sensorRead(sensor->first);
        }


        theSchoolBus.sendSensorData(msgID,sensorReads[0], sensorReads[1], sensorReads[2], sensorReads[3]);
        theSchoolBus.sendSensorData(msgID+1,sensorReads[4], sensorReads[5], sensorReads[6], sensorReads[7]);
        theSchoolBus.sendStateReport(millis(), myRocket.getState(), myRocket, alara);
        lastCANReport = time;
    }

    return;
}

// TODO:: helper function for safety features
//      Ping loss
//      Lox pressure

void fireRoutine(int zeroTime) {
    int curMillis = zeroTime;
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
        if (curMillis > FMVCloseTime && curMillis > FMVCloseTime) {
            return;
        }
    }
}

void fireRoutineSetup() {
    int time = millis();
    return fireRoutine(time);
}

void writeSDReport(char* fileLogName) {
    if (sd_write) {   
        File onBoardLog = SD.open(fileLogName, FILE_WRITE);   
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
        onBoardLog.printf("Time (ms) : %s", entry + "\n");
    }
}

// The Zero PTs function currently does not work. You also can't use it from test mode. 

void executeCommand(uint32_t commandID) {

    //*************************
    if(commandID != 255 && commandID != 131 && commandID != 132 && commandID != 128)
        Serial.println(commandID);
    //*************************
    

    if (commandID <= TEST && state_transitions[myRocket.getState()][commandID]) 
        myRocket.changeState(commandID);
    else if (commandID == FIRE) 
        fireRoutineSetup();
    else if (myRocket.getState() == TEST) 
    {
        if (commandID <= IGN2_OFF) 
            myRocket.setIgnitionOn(commandID / 2, commandID % 2);
        else if (commandID <= FMV_OPEN) 
            myRocket.setValveOn(commandID / 2, commandID % 2);
    }
    else if (commandID == 42) {
        lastPing = millis() - lastPing;
        theSchoolBus.ping();
    }
    else if (commandID == ZERO_PTS)
    {
        if(calibratedPTs == true)
        {
            myRocket.calibrateSensors(alara);
        }
        else
        {
            // Go fish.
        }
        
        Serial.println("HEY!");
    }
    else if (commandID == GET_LMV_OPEN)
        theSchoolBus.sendTiming(SEND_LMV_OPEN);
    else if (commandID == GET_FMV_OPEN)
        theSchoolBus.sendTiming(SEND_FMV_OPEN);
    else if (commandID == GET_LMV_CLOSE)
        theSchoolBus.sendTiming(SEND_LMV_CLOSE);
    else if (commandID == GET_FMV_CLOSE)
        theSchoolBus.sendTiming(SEND_FMV_CLOSE);
    else if (commandID == PING_PI_ROCKET)
        theSchoolBus.ping();
}

void safetyChecks() {
    //if(lastPing > 5000 /*lox_pressure > xxx*/) myRocket.changeState(VENT);
}


// TODO:: add LEDs

void setup() {
    
    Serial.begin(9600);
    Serial.println("Serial Test");
    Wire.begin();
    SPI.begin();

    /*
    if (!SD.begin(BUILTIN_SDCARD)) {
        sd_write = false;
    }
    */
    myRocket = Rocket(alara);

    Can0.begin(CAN2busSpeed);
    Can0.setTxBufferSize(64);


    // Do we want default values?
    ignitionTime = 0;
    LMVOpenTime = 0;
    FMVOpenTime = 0;
    LMVCloseTime = 0;
    FMVCloseTime = 0;


    //uint32_t verifier = 255;
}

void loop() {
    executeCommand(theSchoolBus.readMessage());
    CANRoutine(millis());
    writeSDReport(fileLogName);
}
