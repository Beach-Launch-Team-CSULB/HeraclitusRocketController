#include "Rocket.h"
#include <iostream>

// Constructor definition
Rocket::Rocket() {}

// Method definitions
int Rocket::sensorRead(int sensorReading) {
    // Reads values from a sensor 

}

int Rocket::ignitionRead(int ignitionReading) {
    // Reads values from igniters
}

int Rocket::valveRead(int valveReading) {
    // Reads values from valves 
}

int Rocket::setIgnitionOn(int ignitionOn) {
    // Implementation for toggling ignition
    
}

int Rocket::setValveOn(int valveOpen) {
    //
}

bool Rocket::getExecuting(){
    return this->executingCommand;
}

int Rocket::createValve(int valveID){
    // Creates a valve object
}

int Rocket::createIgnition(int valveID){
    // Creates an Igniter Object
}

int Rocket::createSensor(int valveID){
    // Create a Sensor 

}
