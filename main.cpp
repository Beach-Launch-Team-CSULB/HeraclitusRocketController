// Pseudocode for the 'Main' section of the rocket event-handling system
#include <iostream>
#include <array>
#include <unordered_map>
#include <Rocket.h>

Rocket rocket;
 
// I know the command comes in a different format, but for now I'm treating command as
// the list of valves[] coming in from CAN
void processCommand(std::array<int, 12> command) {
    // If a command is valid and no other command is currently executing
    if (commandIsValid(command) && !rocket.getExecuting()) {
        // Execute the command
        executeCommand();
        // Confirm update status
        confirmUpdateStatus();
    }
}

void executeCommand(std::array<int, 12> command) {
    // Add setter() for rocket
    for (size_t i = 0; i < validCommandTable[rocket.curState].size(); ++i) {
        if (validCommandTable[rocket.curState][i] == 1) {
            rocket.setValveOn(i, true)
        }
        else if (validCommandTable[rocket.curState][i] == 0){
            rocket.setValveOn(i, false)
        }

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
// Valid: [1, 0, 0, 1]
// Incoming: [0, 0, 0, 1]
bool commandIsValid(std::array<int, 12> command) {
    for (size_t i = 0; i < validCommandTable[rocket.curState].size(); ++i) {
        // If there's a 1 in 'valid' but not in the same position in 'incoming', it's not valid.
        if (validCommandTable[rocket.curState][i] == 1 && command[i] != 1) {
            return false;
        }
        else {
            return true;
        }
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

// combining LoxPressure and LoxPressureTooHigh into one function
bool checkLoxPressure() {
    const int loxPressureSensorId = /* appropriate sensor ID */;
    const int pressureThreshold = /* define your threshold */;

    int loxPressure = rocket.sensorRead(loxPressureSensorId);

    return loxPressure > pressureThreshold;
}

bool executeVentCommand() {
    // Implementation depends on how the vent command is executed
    if (checkLoxPressure() = true) {
        
    }
}

void confirmUpdateStatus() {
    // if message is received from rocket, then we give thumbs up
}

void ignition() {
    int ignitionStatus = rocket.ignitionRead();
    if (ignitionStatus == 1) {
        rocket.setIgnitionOn == 1
    }
    else {
        rocket.setIgnitionOff == 0
    }
}

// Main program loop
int main() {
    Main mainSystem;

    /*
    Initiate and Populate Command Table Hashmap with valid valves
        0 = Unpowered & Unresponsive
        1 = Powered & Responsive
        2 = Powered & Time-Sensitive 
    */
    static std::unordered_map<std::string, std::array<int, 12>> validCommandTable;
    validCommandTable["Test"] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    validCommandTable["Passive"] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    validCommandTable["Standby"] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    validCommandTable["High Press"] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    validCommandTable["Tank Press"] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}
    validCommandTable["Fire"] = {1, 0, 0, 2, 1, 0, 0, 2, 1, 0, 2, 2}
    validCommandTable["Abort"] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}


    while (true) {
        // Process incoming commands
        mainSystem.processCommand();

        // Handle sensor data if available
        mainSystem.handleSensorData();

        // Monitor and control LOX pressure
        mainSystem.monitorPressure();

    }
}
