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
#include "CommandManager.h"
#include "DelayedAction.h"

// These need to not have a value or the value will be set to that throughout the duration of the program.
// Defined globally, initialized in setup(), and modified by readMessage() in CANDriver.cpp
uint32_t ignitionTime;
uint32_t LMVOpenTime;
uint32_t FMVOpenTime;
uint32_t LMVCloseTime;
uint32_t FMVCloseTime;

int alara = ALARA;
File onBoardLog;
char* fileLogName = "SoftwareTest-03-15-2024.txt";
bool sd_write = true;
Rocket myRocket = Rocket();

unsigned long currentTime;
unsigned long prevGUIReportTime;
unsigned long prevSDReportTime;


// TO BE REMOVED AT THE END OF CAN TEST

const int CAN2busSpeed = 500000;
CANDriver comSys = CANDriver();

// Simulating PT readings
#define FAKEDATA1     ((float) 0.00)
#define FAKEDATA2     ((float) 27.00)
#define FAKEDATA3     ((float) 42.00)
#define FAKEDATA4     ((float) 655.35)

#define CANID_1  ((uint32_t) 1)
#define CANID_2  ((uint32_t) 2)
#define CANID_3  ((uint32_t) 3)
#define CANID_4  ((uint32_t) 4)
#define CANID_5  ((uint32_t) 5)
#define CANID_6  ((uint32_t) 6)
#define CANID_7  ((uint32_t) 7)
#define CANID_8  ((uint32_t) 8)
#define CANID_9  ((uint32_t) 9)
#define CANID_10 ((uint32_t) 10)



void setup() {
    
    Serial.begin(9600);
    Serial.println("Serial Test");
    Wire.begin();
    SPI.begin();
    if (!SD.begin(BUILTIN_SDCARD)) {
        sd_write = false;
    }

    //myRocket = Rocket(alara);
    //ExtendedIO::extendedIOsetup();

    CommandManager::init(&myRocket, &comSys);
    DelayedAction::init(&myRocket);
    
    Serial.println("opening program!");

    Can0.begin(CAN2busSpeed);
    Can0.setTxBufferSize(64);
    uint32_t verifier = 255;

    // Do we want default values?
    ignitionTime = 0;
    LMVOpenTime = 0;
    FMVOpenTime = 0;
    LMVCloseTime = 0;
    FMVCloseTime = 0;
}


void loop() {
    currentTime = millis();

    CommandManager::checkCommand();
    DelayedAction::performActions(currentTime);
        
    Serial.println("plz");

    if(currentTime >= prevGUIReportTime + 250)
    {
        comSys.sendStateReport(currentTime, myRocket.currentState, myRocket, ALARA);
        //comSys.sendSensorData()
        prevGUIReportTime = currentTime;
    }


}