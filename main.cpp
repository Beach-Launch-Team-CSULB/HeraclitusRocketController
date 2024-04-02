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
#include <iostream>

uint32_t ignitionTime = 0;
uint32_t LMVOpenTime  = 0;
uint32_t FMVOpenTime  = 0;
uint32_t LMVCloseTime = 0;
uint32_t FMVCloseTime = 0;


int alara = 0;
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

}

void loop() {

    

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
 *   /// CAN 2.0 Engine Node ///
 *   1.)  Receives [3] from Pi Box
 *   2.)  Sends [4] to Pi Box
 *  
 *   3.)  Receives [6] from Propulsion Node
 *   4.)  Sends [7] to Pi Box
 * 
 *   6.)  Receives [8] from Pi Box
 *   5.)  Sends [9] to Propulsion Node
 */

  if(verifier == 3)
  {
    //test.sendStateReport(1000007,);
    test.sendSensorData(4,FAKEDATA1,FAKEDATA2,FAKEDATA3,FAKEDATA4);
    verifier = 0;
  }
  if(verifier == 6)
  {
    test.sendSensorData(7,FAKEDATA1,FAKEDATA2,FAKEDATA3,FAKEDATA4);
    verifier = 0;
  }
  if(verifier == 8)
  {
    test.sendSensorData(9,FAKEDATA1,FAKEDATA2,FAKEDATA3,FAKEDATA4);
    verifier = 0;
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
