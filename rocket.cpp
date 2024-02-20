#include <Rocket.h>
#include <Valve.h>
#include <Igniter.h>
#include <Thermocouple.h>
#include <LoadCell.h>
#include <PressureTransducer.h>
#include <iostream>

// Constructor definition
Rocket::Rocket(){
    //Creates all components on construction 
    
    //Igniter igniter(int igniterID,int 11,pinDigital,pinPWM,igniterOn,defaultStateON);
}

// Method definitions
int Rocket::sensorRead(int sensorID) {
    // Reads values from a sensor 
}

bool Rocket::ignitionRead(int igniterID) {
    // Reads values from igniters
}

bool Rocket::valveRead(int valveID) {
    // Reads values from valves 
}

bool Rocket::setIgnitionOn(int igniterID, bool isignitionOn) {
    // Implementation for toggling ignition
}

bool Rocket::setValveOn(int igniterID,bool isvalveOpen) {
    //
}

bool Rocket::getExecuting(){
    return this->executingCommand;
}

