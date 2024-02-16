#include <Rocket.h>
#include <iostream>

// Constructor definition
Rocket::Rocket() {}

// Method definitions
int Rocket::sensorRead(int sensorID) {
    // Reads values from a sensor 
}

int Rocket::ignitionRead(int igniterID) {
    // Reads values from igniters
}

int Rocket::valveRead(int valveID) {
    // Reads values from valves 
}

int Rocket::setIgnitionOn(int isignitionOn) {
    // Implementation for toggling ignition
    
}

int Rocket::setValveOn(int isvalveOpen) {
    //
}

bool Rocket::getExecuting(){
    return this->executingCommand;
}

bool Rocket::createValve(int valveID){
    // Creates a valve object
}

bool Rocket::createIgnition(int valveID){
    // Creates an Igniter Object
}

bool Rocket::createSensor(int valveID){
    // Create a Sensor 

}
