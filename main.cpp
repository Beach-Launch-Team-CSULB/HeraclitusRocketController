#include "Arduino.h"
#include <iostream>
#include <array>
#include <unordered_map>
#include "Rocket.h"
#include "Igniter.h"
#include <unistd.h> // NOTE:: Analicia_4/11/24_Midnight:: Do we still need this? If not let's remove it
#include <SD.h>
#include <SPI.h>
#include "ExtendedIO.h"
#include <Wire.h>

#include <FlexCAN.h> // NOTE:: *   Analicia_4/11/24_Midnight:: Let's get to the point where we only need to include CANDriver
#include "CANDriver.h"
#include <cstdint>
#include "Config.h"

// These need to not have a value or the value will be set to that throughout the duration of the program.
// Initialize in setup()

/*
 *
 *   Analicia_4/11/24_Midnight
 *   NOTE: Do these need to be declared here? They're already declared in config.
 *
 */
uint32_t LMVOpenTime;
uint32_t FMVOpenTime;
uint32_t LMVCloseTime;
uint32_t FMVCloseTime;

/* 
 * If you put this in config it will throw an error for every additional place that you have #include "Config.h"
 * (CANDriver, LED Controller, main, and Rocket). I experienced a similar issue when trying to implement the times.
 * Ultimately, you end up using an extern declaration in config, and then a global declaration in the actual file where
 * the variable will be used (in our case main). This allows for them to be modified within the CANDriver class.
 * 
 * Since the state_transitions are not modified by another part of the program we do not need an extern definition within Config.h.
 * However, we would need to have this in here regardless.
 * 
 */
int state_transitions[9][9] = {
    //                                          TO
    //                  ABORT, VENT, IGNITE   FIRE, TANK_PRESS, HIGH_PRESS, STANDBY, TEST, MANUAL_VENT
    /*      ABORT */     {0,    1,     0,       0,    0,         0,          1,       0,    0},
    /*      VENT */      {1,    0,     0,       0,    0,         0,          1,       0,    0},
    /* F    IGNITE*/     {1,    1,     0,       1,    0,         0,          0,       0,    1},
    /* R    FIRE */      {1,    1,     0,       0,    0,         0,          1,       0,    0},
    /* O    TANK_PRESS */{1,    1,     0,       0,    0,         1,          0,       0,    1},
    /* M    HIGH_PRESS */{1,    1,     1,       0,    0,         0,          0,       0,    1},
    /*      STANDBY */   {1,    1,     0,       0,    0,         0,          0,       0,    1},
    /*      TEST */      {1,    1,     0,       0,    1,         0,          0,       0,    0},
    /*      MANUAL_VENT*/{1,    1,     0,       0,    0,         0,          0,       0,    0}
};


/*
*
*   Analicia_4/11/24_Midnight
*   TODO:: Modify this so it grabs the current date for the file name
*
*/
char* fileLogName = "SoftwareTest-03-15-2024.txt";
File onBoardLog;
bool sd_write = true;
int alara = ALARA_ID;              // 4/11: Attempting to resolve build issue
Rocket myRocket = Rocket(alara);
CANDriver canBus = CANDriver();
int lastPing;
int lastCANReport;

// TO BE REMOVED AT THE END OF CAN TEST



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

uint32_t verifier;
CANDriver test = CANDriver();
bool calibratedPTs; // Global variable initialized as zero.

/*
*
*   Analicia_4/11/24_Midnight
*   TODO:: What happens if we don't care whether we close the valves and don't set close times
*
*/
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

void executeCommand(uint32_t commandID) {
    if (commandID <= TEST && state_transitions[myRocket.getState()][commandID]) myRocket.changeState(commandID);
    if (commandID == FIRE) fireRoutineSetup();
    else if (myRocket.getState() == TEST) {
        if (commandID <= IGN2_OFF) myRocket.setIgnitionOn(commandID / 2, commandID % 2);
        else if (commandID <= FMV_OPEN) myRocket.setValveOn(commandID / 2, commandID % 2);
    }
    else if (commandID == 42) {
        lastPing = millis() - lastPing;
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
    }
    else if (commandID == GET_LMV_OPEN)
        test.sendTiming(SEND_LMV_OPEN);
    else if (commandID == GET_FMV_OPEN)
        test.sendTiming(SEND_FMV_OPEN);
    else if (commandID == GET_LMV_CLOSE)
        test.sendTiming(SEND_LMV_CLOSE);
    else if (commandID == GET_FMV_CLOSE)
        test.sendTiming(SEND_FMV_CLOSE);
    else if (commandID == PING_PI_ROCKET)
        test.ping();
    }

// void writeSDReport(file) {


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

        test.sendSensorData(msgID,sensorReads[0], sensorReads[1], sensorReads[2], sensorReads[3]);
        test.sendSensorData(msgID+1,sensorReads[4], sensorReads[5], sensorReads[6], sensorReads[7]);
        test.sendStateReport(millis(), myRocket.getState(), myRocket, alara);

        lastCANReport = time;
    }
    return;
}

/*
*
*   Analicia_4/11/24_Midnight
*   TODO:: Add lox voltage for override
*
*/
void safetyChecks() {
    if(lastPing > 5000 /*lox_pressure > xxx*/) myRocket.changeState(VENT);
}


// TODO:: add LEDs

/*
 *
 *  To do: 
 *          1.) See if idea for "zeroing" the PTs will work.
 *          2.) Command handling is built in, define calibration function in rocket.cpp
 * 
 * 
 */


void setup() {
    
    Serial.begin(9600);
    Serial.println("Serial Test");
    Wire.begin();
    SPI.begin();
    if (!SD.begin(BUILTIN_SDCARD)) {
        sd_write = false;
    }
    onBoardLog = SD.open(fileLogName, FILE_WRITE);
    myRocket = Rocket(alara);


    Can0.begin(CAN_BAUD_RATE);                      // See if this can go in CANDriver()
    Can0.setTxBufferSize(CAN_TX_BUFFER);            // See if this can go in CANDriver()

    LMVOpenTime = LMV_OPEN_TIME_DEFAULT;
    FMVOpenTime = FMV_OPEN_TIME_DEFAULT;
    LMVCloseTime = LMV_CLOSE_TIME_DEFAULT;
    FMVCloseTime = FMV_CLOSE_TIME_DEFAULT;

    calibratedPTs = false;


}


void loop() {

    // See if this works - 
    /*static uint32_t nextCANTime;

    // Static Methods?
    uint32_t verifier = test.readMessage();
    if (verifier != 255)
    {
        Serial.println("Main: ");
        Serial.println(verifier);
    }
*/

    executeCommand(canBus.readMessage());
    CANRoutine(millis());
    writeSDReport(fileLogName);

// Note: 4/10/2024
// - Test the ability to receive a CAN state report (cast output as an int)
// Serial.println();
// - Test the ability to zero PTs.


  

  //Serial.println(LMVOpenTime);
    // Added in this


/*
  // Changing this first id only.
  if(verifier == 1)
  {
    // Added in this
    // Fuel Vent.////
    myRocket.setValveOn(LDV_ID, true);
    test.sendStateReport(0, FIRE, myRocket, 1);     // Added
    delay(500);                                      // Added
    myRocket.setValveOn(FDV_ID, true);               // Added
    test.sendStateReport(0, FIRE, myRocket, 1);     // Added
    delay(500);
    // Try passing in the value of "alara" from setup as the boolean value.
    //test.sendStateReport(1, TEST, myRocket, true);
    delay(500);                                    // Added 
    myRocket.setValveOn(LDV_ID, false);            // Added 
    test.sendStateReport(0, TEST, myRocket, 1);    // Added 
    test.sendStateReport(0, TEST, myRocket, 1);    // Added 
    test.sendStateReport(0, TEST, myRocket, 1);    // Added 
    delay(500);                                    // Added 
    myRocket.setValveOn(FDV_ID, false);             // Added 
    test.sendStateReport(0, TEST, myRocket, 1);    // Added 
    test.sendStateReport(0, TEST, myRocket, 1);    // Added
    test.sendStateReport(0, TEST, myRocket, 1);    // Added 

    //Serial.println(ignitionTime);
    test.sendTiming(GET_LMV_OPEN);
    test.sendSensorData(2,FAKEDATA1,FAKEDATA2,FAKEDATA3,FAKEDATA4);
    verifier = 0;
  }
  if(verifier == CANID_5)
  {
    test.sendSensorData(6,FAKEDATA1,FAKEDATA2,FAKEDATA3,FAKEDATA4);
    test.sendStateReport(0, TEST, myRocket, 1); // Added
    verifier = 0;
  }
  if(verifier == CANID_9)
  {
    test.sendSensorData(10,FAKEDATA1,FAKEDATA2,FAKEDATA3,FAKEDATA4);
    test.sendStateReport(0, TEST, myRocket, 1); // Added
    verifier = 0;
  }

  delay(1000);                                   // Added
  test.sendStateReport(0, FIRE, myRocket, 1);    // Added
  */
  

  






// SD Card and CAN Send

// *** Note: The enum for the rocket states have values that are inconsistent with the IDs for CAN messages. Ask about this. ***
/*    if(alara == 1) // Propulsion Node
    {
        int time = millis(); // Double check. This should be fine as long as the ALARA doesn't run for 3 weeks+.
        uint8_t state = myRocket.getState();

        std::string sTime  = std::to_string(time);
        std::string sState = std::to_string(state);

        std::string sPTLoxHigh   = std::to_string(myRocket.sensorRead(PT_LOX_HIGH_ID));
        std::string sPTFuelHigh  = std::to_string(myRocket.sensorRead(PT_FUEL_HIGH_ID));
        std::string sPTLoxDome   = std::to_string(myRocket.sensorRead(PT_LOX_DOME_ID));
        std::string sPTFuelDome  = std::to_string(myRocket.sensorRead(PT_FUEL_DOME_ID));

        std::string sPTLoxTank1  = std::to_string(myRocket.sensorRead(PT_LOX_TANK_1_ID));
        std::string sPTLoxTank2  = std::to_string(myRocket.sensorRead(PT_LOX_TANK_2_ID));
        std::string sPTFuelTank1 = std::to_string(myRocket.sensorRead(PT_FUEL_TANK_1_ID));
        std::string sPTFuelTank2 = std::to_string(myRocket.sensorRead(PT_FUEL_TANK_2_ID));

        char LVState  = (myRocket.valveRead(LV_ID)  ? '1' : '0');
        char LDVState = (myRocket.valveRead(LDV_ID) ? '1' : '0');
        char LDRState = (myRocket.valveRead(LDR_ID) ? '1' : '0');
        char FVState  = (myRocket.valveRead(FV_ID)  ? '1' : '0');
        char FDVState = (myRocket.valveRead(FDV_ID) ? '1' : '0');
        char FDRState = (myRocket.valveRead(FDR_ID) ? '1' : '0');

        std::string entry = sTime + " | State: " + sState + " | LV: " + LVState + " | LDV: " + LDVState + " | LDR: " + LDRState +
                            " | FV: " + FVState + " | FDV: " + FDVState + " | FDR: " + FDRState + " | PTLox High: " + sPTLoxHigh + 
                            " | PTFuel High: " + sPTFuelHigh + " | PTLox Dome: " + sPTLoxDome + " | PTFuel Dome: " + sPTFuelDome +
                            " | PTLox Tank1: " + sPTLoxTank1 + " | PTLox Tank2: " + sPTLoxTank2 + " | PTFuel Tank1: " + sPTFuelTank1 +
                            " | PTFuel Tank2: " + sPTFuelTank2 + '\n';

        if (sd_write) 
        {
            File onBoardLog = SD.open(fileLogName, FILE_WRITE);
            onBoardLog.printf("Time (ms) : %s", entry);
        }

        // Only occurs three times per second
        if(millis() - nextCANTime >= CAN_INTERVAL)
        {
            // Update time
            nextCANTime += CAN_INTERVAL;

            // Do CAN tasks
            float PTLoxHigh   = myRocket.sensorRead(PT_LOX_HIGH_ID);
            float PTFuelHigh  = myRocket.sensorRead(PT_FUEL_HIGH_ID);
            float PTLoxDome   = myRocket.sensorRead(PT_LOX_DOME_ID);
            float PTFuelDome  = myRocket.sensorRead(PT_FUEL_DOME_ID);

            float PTLoxTank1  = myRocket.sensorRead(PT_LOX_TANK_1_ID);
            float PTLoxTank2  = myRocket.sensorRead(PT_LOX_TANK_2_ID);
            float PTFuelTank1 = myRocket.sensorRead(PT_FUEL_TANK_1_ID);
            float PTFuelTank2 = myRocket.sensorRead(PT_FUEL_TANK_2_ID);

            test.sendSensorData(SENS_1_4_PROP, PTLoxHigh, PTFuelHigh, PTLoxDome, PTFuelDome);
            test.sendSensorData(SENS_5_8_PROP, PTLoxTank1, PTLoxTank2, PTFuelTank1, PTFuelTank2);
            test.sendStateReport(time, state, myRocket, alara);
        }
    }
    else // Engine Node
    {
        int time = millis();
        uint8_t state = myRocket.getState(); 

        std::string sTime  = std::to_string(time);
        std::string sState = std::to_string(state);

        std::string sPTPneumatics   = std::to_string(myRocket.sensorRead(PT_PNUEMATICS_ID));
        std::string sPTLoxInlet     = std::to_string(myRocket.sensorRead(PT_LOX_INLET_ID));
        std::string sPTFuelInlet    = std::to_string(myRocket.sensorRead(PT_FUEL_INLET_ID));
        std::string sPTFuelInjector = std::to_string(myRocket.sensorRead(PT_FUEL_INJECTOR_ID));

        std::string sPTChamber1     = std::to_string(myRocket.sensorRead(PT_CHAMBER_1_ID));
        std::string sPTChamber2     = std::to_string(myRocket.sensorRead(PT_CHAMBER_2_ID));

        char HPState   = (myRocket.valveRead(HP_ID)      ? '1' : '0');
        char HVState   = (myRocket.valveRead(HV_ID)      ? '1' : '0');
        char FMVState  = (myRocket.valveRead(FMV_ID)     ? '1' : '0');
        char LMVState  = (myRocket.valveRead(LMV_ID)     ? '1' : '0');
        char IGN1State = (myRocket.ignitionRead(IGN1_ID) ? '1' : '0');
        char IGN2State = (myRocket.ignitionRead(IGN2_ID) ? '1' : '0');

        std::string entry = sTime + " | State: " + sState + " | HP: " + HPState + " | HV: " + HVState + " | FMV: " + FMVState  +
                            " | LMV: " + LMVState + " | IGN1: " + IGN1State + " | IGN2: " + IGN2State + " | PTPneumatics: " + 
                            sPTPneumatics + " | PTLox Inlet: " + sPTLoxInlet + " | PTFuel Inlet: " + sPTFuelInlet + " | PTFuel Injector: " +
                            sPTFuelInjector + " | PTChamber1: " + sPTChamber1 + " | PTChamber2: " + sPTChamber2 + '\n';

        if (sd_write) 
        {
            File onBoardLog = SD.open(fileLogName, FILE_WRITE);
            onBoardLog.printf("Time (ms) : %s", entry);
        }

        // Only occurs three times per second
        if(millis() - nextCANTime >= CAN_INTERVAL)
        {
            // Update time
            nextCANTime += CAN_INTERVAL;

            // Do CAN tasks
            float PTPneumatics   = myRocket.sensorRead(PT_PNUEMATICS_ID);
            float PTLoxInlet     = myRocket.sensorRead(PT_LOX_INLET_ID);
            float PTFuelInlet    = myRocket.sensorRead(PT_FUEL_INLET_ID);
            float PTFuelInjector = myRocket.sensorRead(PT_FUEL_INJECTOR_ID);

            float PTChamber1     = myRocket.sensorRead(PT_CHAMBER_1_ID);
            float PTChamber2     = myRocket.sensorRead(PT_CHAMBER_2_ID);

            test.sendSensorData(SENS_9_12_ENGINE,PTPneumatics, PTLoxInlet, PTFuelInlet, PTFuelInjector);
            test.sendSensorData(SENS_13_16_ENGINE,PTChamber1, PTChamber2, 0, 0);
            test.sendStateReport(time, state, myRocket, alara);
        }
    }*/
}
