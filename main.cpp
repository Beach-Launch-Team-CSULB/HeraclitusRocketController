#include "Arduino.h"
#include <iostream>
#include <array>
#include <unordered_map>
#include "Rocket.h"
#include "CANDriver.h"
#include "Arduino.h"
//#include "Sensor.h"
#include "Igniter.h"
#include <unistd.h> // For sleep function
#include <SD.h>
#include <SPI.h>
#include "ExtendedIO.h"
#include <Wire.h>

int alara = 1;
File onBoardLog;
char* fileLogName = "SoftwareTest-03-15-2024.txt";
bool sd_write = true;
Rocket myRocket = Rocket(alara);

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

}

void loop() {
    
    /*Igniter();
    for (const auto& pair : myRocket.igniterMap) {
        myRocket.setIgnitionOn(pair.first, true);
 S       //sleep(1);
        delay(1);
        myRocket.setIgnitionOn(pair.first, false);
        //sleep(1);
        delay(1);
    }*/

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

        myRocket.setValveOn(24, false);
        //sleep(1);
        

        /// MILISECONDS
        delay(1000);
 /*

        myRocket.setValveOn(25, true);
        //sleep(1);
        delay(1000);
        myRocket.setValveOn(25, false);
        //sleep(1);

        /// MILISECONDS
        delay(1000);
        myRocket.setValveOn(26, true);
        //sleep(1);
        delay(1000);
        myRocket.setValveOn(26, false);
        //sleep(1);

        /// MILISECONDS
        delay(1000);
        myRocket.setValveOn(27, true);
        //sleep(1);
        delay(1000);
        myRocket.setValveOn(27, false);
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
    */
    
    //delay(5000);
   
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
}
*/