
#include <iostream>
#include "Rocket.h"
#include "Valve.h"
#include "Igniter.h"
#include "Sensor.hpp"
#include "Thermocouple.h"
#include "LoadCell.h"
#include "PressureTransducer.h"
#include "Config.h"

// Constructor definition
Rocket::Rocket(int ALARA){
    if (ALARA == 0){                             // Lower ALARA Setup 
        initializeIgniters();
        initializeLowerValves();
    }
    if (ALARA == 1){                             // Upper ALARA Setup
        initializeUpperValves();
    }
}

// Method definitions
int Rocket::sensorRead(int sensorID) {
    // Reads values from a sensor 
}

bool Rocket::ignitionRead(int igniterID) {
    
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

bool Rocket::initializeUpperValves(){
    Valve HP(HP_ID,HP_PIN_PWM,HV_PIN_DIG);      // High Press Valve
    Valve HV(HV_ID,HV_PIN_PWM,HV_PIN_DIG);      // High Vent Valve 
    Valve FMV(FMV_ID,FMV_PIN_PWM,FMV_PIN_DIG);  // Fuel Main Valve
    Valve LMV(LMV_ID,LMV_PIN_PWM,LMV_PIN_DIG);  // Lox Main Valve
    return true;
}

bool Rocket::initializeLowerValves(){
    Valve LV(LV_ID,LV_PIN_PWM,LV_PIN_DIG);      // Lox Vent Valve
    Valve LDV(LDV_ID,LDV_PIN_PWM,LDV_PIN_DIG);  // Lox Dome Vent Valve
    Valve LDR(LDR_ID,LDR_PIN_PWM,LDR_PIN_DIG);  // Lox Dome Reg Valve
    Valve FV(FV_ID,FV_PIN_PWM,FV_PIN_DIG);      // Fuel Vent Valve
    Valve FDV(FDV_ID,FDV_PIN_PWM,FDV_PIN_DIG);  // Fuel Dome Vent Valve
    Valve FDR(FDR_ID,FDR_PIN_PWM,FDR_PIN_DIG);  // Fuel Dome Reg Valve
    return true;
}

bool Rocket::initializeSensors(){
    //for(i = 0; i < ; i++)
    {
        
    }
}


