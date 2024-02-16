#include <Rocket.h>
#include <Valve.h>
#include <Igniter.h>
#include <Thermocouple.h>
#include <LoadCell.h>
#include <PressureTransducer.h>
#include <iostream>

// Constructor definition
Rocket::Rocket(){
    
    //Igniter igniter(igniterID,int 11,pinDigital,pinPWM,igniterOn,defaultStateON);
}

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

