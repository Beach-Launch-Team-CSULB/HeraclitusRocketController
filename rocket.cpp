
#include <iostream>
#include "Rocket.h"
#include "Valve.h"
#include "Igniter.h"
#include "Thermocouple.h"
#include "LoadCell.h"
#include "PressureTransducer.h"
#include "Config.h"

// Constructor definition
Rocket::Rocket(){
    // Create Igniter Objects 
    initializeIgniters()

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


bool Rocket::initializeIgniters(){
    Igniter Igniter1(IGN1_ID, IGN1_PIN_PWM,IGN1_PIN_DIG);
    Igniter Igniter2(IGN2_ID, IGN2_PIN_PWM,IGN2_PIN_DIG); 
    return true;
}

bool Rocket::initializeValves(){
    Valve 
    return true;
}



bool Rocket::initializeSensors(){
    //for(i = 0; i < ; i++)
    {
        
    }
}


