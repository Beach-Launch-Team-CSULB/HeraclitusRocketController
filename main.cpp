#include "Arduino.h"
#include <iostream>
#include <array>
#include <unordered_map>
#include "Rocket.h"
#include "CANDriver.h"
//#include "Arduino.h"
//#include "Sensor.h"
#include "Igniter.h"
#include <unistd.h> // For sleep function
#include <SD.h>
#include <SPI.h>
#include "ExtendedIO.h"
#include <Wire.h>



#include <FlexCAN.h>

#include <ios>
#include "CANDriver.h"


File onBoardLog;
char* fileLogName = "SoftwareTest-03-15-2024.txt";
bool sd_write = true;
Rocket myRocket = Rocket();

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
    //myRocket = Rocket();
    //ExtendedIO::extendedIOsetup();

    myRocket.ledArray.init();

    Can0.begin(CAN2busSpeed);
    Can0.setTxBufferSize(64);
    uint32_t verifier = 0;
    
    myRocket.setLED(0, GRAY);
    myRocket.setLED(1, GRAY);
    delay(500);
    //myRocket.setLED(1, TEAL);



}

void loop() {
//testing delay


/* //testing colors
    myRocket.setLED(0, RED);
    delay(500);
    myRocket.setLED(1, RED);
    delay(500);

    myRocket.setLED(0, ORANGE);
    delay(500);
    myRocket.setLED(1, ORANGE);
    delay(500);
    
    myRocket.setLED(0, YELLOW);
    delay(500);
    myRocket.setLED(1, YELLOW);
    delay(500);
    
    myRocket.setLED(0, LIME);
    delay(500);
    myRocket.setLED(1, LIME);
    delay(500);
    
    myRocket.setLED(0, GREEN);
    delay(500);
    myRocket.setLED(1, GREEN);
    delay(500);

    myRocket.setLED(0, CYAN);
    delay(500);
    myRocket.setLED(1, CYAN);
    delay(500);
    
    myRocket.setLED(0, TEAL);
    delay(500);
    myRocket.setLED(1, TEAL);
    delay(500);

    myRocket.setLED(0, BLUE);
    delay(500);
    myRocket.setLED(1, BLUE);
    delay(500);

    myRocket.setLED(0, PURPLE);
    delay(500);
    myRocket.setLED(1, PURPLE);
    delay(500);
    
    myRocket.setLED(0, MAGENTA);
    delay(500);
    myRocket.setLED(1, MAGENTA);
    delay(500);
    
    myRocket.setLED(0, PINK);
    delay(500);
    myRocket.setLED(1, PINK);
    delay(500);

*/

    /*
        /// MILISECONDS
        delay(1000);
        myRocket.setValveOn(myRocket.valveIDArray[4], true);
        //sleep(1);
        delay(1000);
        myRocket.setValveOn(myRocket.valveIDArray[4], false);
        //sleep(1);
    */
    
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
}
*/