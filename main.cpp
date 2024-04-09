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

int alara = 1;
File onBoardLog;
char* fileLogName = "SoftwareTest-03-15-2024.txt";
bool sd_write = true;
Rocket myRocket = Rocket(alara);

// TO BE REMOVED AT THE END OF CAN TEST

const int CAN2busSpeed = 500000;
CANDriver test = CANDriver();

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
    myRocket = Rocket(alara);
    //ExtendedIO::extendedIOsetup();

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

    // See if this works - 
    static uint32_t nextCANTime;

    //return;
    /*Igniter();
    for (const auto& pair : myRocket.igniterMap) {
        myRocket.setIgnitionOn(pair.first, true);
 S       //sleep(1);
        delay(1);
        myRocket.setIgnitionOn(pair.first, false);
        //sleep(1);
        delay(1);
    }*/




    // ONLY COMMENTED OUT FOR CAN TEST. 


    /*
    // You need a delay here or the first print will not work. 
    delay(1000);
    int address = 0x400FF100;       //PDOR for LV valve 
    int* pcontent = (int*)address;
    int content = *pcontent;

    int pcr_address = 0x4004C028;       //PCR for LV valve PTD10
    int* pcr_pcontent = (int*)address;
    int pcr_content = *pcontent;

    int pddr_address = 0x400FF0D4;       //PDDR for LV valve
    int* pddr_pcontent = (int*)address;
    int pddr_content = *pcontent;
    

    Serial.println("PDOR BeforeVVV");
    Serial.println(content);
    Serial.println("PCR BeforeVVV");
    Serial.println(pcr_content);
    Serial.println("PDDR BeforeVVV");
    Serial.println(pddr_content);
   
    //for (const auto& pair : myRocket.valveMap) {
        myRocket.setValveOn(24, true);
        //sleep(1);
        delay(1000);
        Serial.println("PDOR AfterVVV");
        Serial.println(content);

        Serial.println("PCR AfterVVV");
        Serial.println(pcr_content);

        Serial.println("PDDR AfterVVV");
        Serial.println(pddr_content);

        myRocket.setValveOn(20, false);
        */

    // TO BE REMOVED AT THE CONCLUSION OF THE CAN TEST


    // Do static methods
    uint32_t verifier = test.readMessage();
    if (verifier != 255)
    {
        Serial.println("Main: ");
        Serial.println(verifier);
    }
    //Serial.println("Working");
    //Serial.println(verifier);

    


 /*
 *   /// CAN 2.0 Propulsion Node ///
 *   1.)  Receives [1] from Pi Box
 *   2.)  Sends [2] to Pi Box
 *  
 *   3.)  Receives [5] from Pi Box
 *   4.)  Sends [6] to Engine Node
 * 
 *   6.)  Receives [9] from Engine Node
 *   5.)  Sends [10] to Pi Box
 */ 


  Serial.println(LMVOpenTime);


  // Changing this first id only.
  if(verifier == 33)
  {
    // Added in this
    delay(500);
    myRocket.setValveOn(LDV_ID, true);
    delay(500);
    // Try passing in the value of "alara" from setup as the boolean value.
    //test.sendStateReport(1, TEST, myRocket, true);
    delay(500);
    myRocket.setValveOn(LDV_ID, false);

    //Serial.println(ignitionTime);
    test.sendTiming(GET_LMV_OPEN);
    test.sendSensorData(2,FAKEDATA1,FAKEDATA2,FAKEDATA3,FAKEDATA4);
    verifier = 0;
  }
  if(verifier == CANID_5)
  {
    test.sendSensorData(6,FAKEDATA1,FAKEDATA2,FAKEDATA3,FAKEDATA4);
    verifier = 0;
  }
  if(verifier == CANID_9)
  {
    test.sendSensorData(10,FAKEDATA1,FAKEDATA2,FAKEDATA3,FAKEDATA4);
    verifier = 0;
  }

// SD Card and CAN Send

// *** Note: The enum for the rocket states have values that are inconsistent with the IDs for CAN messages. Ask about this. ***
    if(alara == 1) // Propulsion Node
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
    }














        //(*(volatile uint32_t *)0x400FF0C0) = (0<<10); //PDOR
        //sleep(1);
        
        /*

        /// MILISECONDS
        delay(1000);
 

        myRocket.setValveOn(21, true);
        //sleep(1);
        delay(1000);
        myRocket.setValveOn(21, false);
        //sleep(1);

        

        /// MILISECONDS
        delay(1000);
        myRocket.setValveOn(22, true);
        //sleep(1);
        delay(1000);
        myRocket.setValveOn(22, false);
        //sleep(1);

        /// MILISECONDS
        delay(1000);
        myRocket.setValveOn(23, true);
        //sleep(1);
        delay(1000);
        myRocket.setValveOn(23, false);
        //sleep(1);

        /// MILISECONDS
        delay(1000);
        myRocket.setValveOn(28, true);
        //sleep(1);
        delay(1000);
        myRocket.setValveOn(28, false);
        //sleep(1);

        /// MILISECONDS
        delay(1000);
        myRocket.setValveOn(29, true);
        //sleep(1);
        delay(1000);
        myRocket.setValveOn(29, false);
        //sleep(1);

        /// MILISECONDS
        delay(1000);
    //}

    
    int address = 0x40048038;
    int* pcontent = (int*)address;
    int content = *pcontent;
    Serial.println(content);

    if (sd_write) {
        File onBoardLog = SD.open(fileLogName, FILE_WRITE);
        for (const auto& sensor : myRocket.sensorMap) {
            onBoardLog.println(myRocket.sensorRead(sensor.first));
        }
    }
}

/*class Main {
    EventManager eventManager;
    Rocket rocket; 

    void processCommand() {
        // If a command is valid and no other command is currently executing
        if (commandIsValid() && !isExecuting()) {
            // Execute the command
            executeCommand();
            // Confirm update status
            confirmUpdateStatus();
        }
    }

    void handleSensorData() {
        // Check if flag for new sensor data is set
        if (isNewSensorDataAvailable()) {
            // Execute sensor data collection
            Event sensorDataEvent = collectSensorData();
            // Return sensor data
            returnSensorData(sensorDataEvent);
        }
    }

    void monitorPressure() {
        // Poll the LOX pressure
        int loxPressure = pollLoxPressure();
        // If LOX pressure is too high
        if (loxPressureTooHigh(loxPressure)) {
            // Execute vent command
            executeVentCommand();
            // Confirm update status
            confirmUpdateStatus();
        }
    }

    // Helper methods
    bool commandIsValid(int idx) {
        if (validCommandTable[rocket.curState][idx] == 1)
            return true;
        else {
            return false;
        }
    }

    bool isExecuting() {
        // Implementation depends on how execution status is tracked
        if (rocket.flag == 0){
            return true;
        }
        else { 
            return false;
        } 
    }

    Event collectSensorData() {
        int sensorReading = rocket.sensorRead();
        Event sensorDataEvent(sensorReading); 
        return sensorDataEvent;
    }

    void returnSensorData(Event& event) {
        // Implementation depends on how sensor data is returned
    }

    int pollLoxPressure() {
        const int loxPressureSensorId = /* appropriate sensor ID ;
        int loxPressure = rocket.sensorRead(loxPressureSensorId);
        return loxPressure;
    }

    bool loxPressureTooHigh(int loxPressure) {
        const int pressureThreshold = /* define your threshold ;
        return pressure > pressureThreshold;
    }

    void executeVentCommand() {
        // Implementation depends on how the vent command is executed
        rocket.toggleValve(ventID, true);
    }

    void confirmUpdateStatus() {
        // if message is received from rocket, then we give thumbs up
    }

};

// Main program loop
int main() {
    Main mainSystem;

    static std::unordered_map<std::string, std::array<int, 12>> validCommandTable;
    validCommandTable["Passive"] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    // Fill out Command Table for final implementation

    while (true) {
        // Process incoming commands
        mainSystem.processCommand();

        // Handle sensor data if available
        mainSystem.handleSensorData();

        // Monitor and control LOX pressure
        mainSystem.monitorPressure();

    }
*/
}

void executeCommand(int commandID) {
    // TODO build in logic for determining whether a state change is valid
    if (commandID < 8) myRocket.changeState(commandID);
    if (myRocket.getState() == 0) {
        else if (commandID < 12) myRocket.setIgnitionOn(commandID / 2, commandID % 2);
        else if (commandID < 32) myRocket.setValveOn(commandID / 2, commandID % 2);
    }
    // else handle the remaining CAN commands
}