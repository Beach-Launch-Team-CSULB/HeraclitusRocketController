
#include <iostream>
#include <map>
#include <utility>
#include "Rocket.h"
#include "Valve.h"
#include "Igniter.h"
#include "Sensor.h"
#include "PressureTransducer.h"
#include "Config.h"

// Constructor definition
Rocket::Rocket(int ALARA)
{
    currentState = Standby;
    // TODO: Set up LEDs?
    if (ALARA == 0) // Lower ALARA Setup
    { 
        initializeIgniters();
        initializeLowerValves();
        initializeLowerSensors();
    }
    if (ALARA == 1) // Upper ALARA Setup
    {
        initializeUpperValves();
        initializeUpperSensors();
    }
}

/*float Rocket::sensorRead(Sensor sensor) {
    return sensor.readDataRaw();
}*/

float Rocket::sensorRead(int sensorId) {
    return sensorMap[sensorId].getCurrentValue(); }

bool Rocket::ignitionRead(int igniterID) {
    return igniterMap[igniterID].getIgniterOn(); }

bool Rocket::valveRead(int valveID) {
    return valveMap[valveID].getValveOpen(); }

bool Rocket::setIgnitionOn(int igniterID, bool ignitionOn) {
    return igniterMap[igniterID].setIgniterOn(ignitionOn); }

bool Rocket::setValveOn(int valveID,bool valveOpen) {
    return valveMap[valveID].setValveOpen(valveOpen); }

bool Rocket::getExecuting(){
    return this->executingCommand; }

// Verifies if the rocket can enter that state, then proceeds to do so
bool Rocket::enterState(E_RocketState stateToEnter)
{
    if(!canEnterState(stateToEnter))
        return false;
    switch(stateToEnter)
    {
        case Vent:
            enterVent();
            return true;
        case Abort:
            enterAbort();
            return true;
        case Fire:
            enterFire();
            return true;
        case TankPress:
            enterTankPress();
            return true;
        case HighPress:
            enterHighPress();
            return true;
        case Test:
            enterTest();
            return true;
        case FireArm:
            enterFireArm();
            return true;
        case TankPressArm:
            enterTankPressArm();
            return true;
        case HighPressArm:
            enterHighPressArm();
            return true;
        case Standby:
            enterStandby();
            return true;
    }
    return false;
}

// Determines if the next state is valid from the current state
bool Rocket::canEnterState(E_RocketState stateToEnter)
{
    switch(stateToEnter)
    {
        case Vent: // Vent is always valid
            return currentState != Vent;
        case Abort: // Abort is always valid
            return currentState != Abort;
        case Standby: // Standby is allowable in any other neutral state
            return (currentState == Vent || currentState == Abort || currentState == Fire || currentState == Test);
        case Test: // Can only be entered from Standby
            return currentState == Standby;

        // Procedural State Check Operations, ordered by importance
        case HighPress:
            return currentState == HighPressArm;
        case TankPress:
            return currentState == TankPressArm;
        case Fire:
            return currentState == FireArm;
        case HighPressArm:
            return currentState == Standby;
        case TankPressArm:
            return currentState == HighPress;
        case FireArm:
            return currentState == TankPress;
    }
}

// Sets up the Igniters on the Lower Engine Node
bool Rocket::initializeIgniters() 
{
    Igniter Igniter1(IGN1_ID, IGN1_PIN_PWM,IGN1_PIN_DIG);
    Igniter Igniter2(IGN2_ID, IGN2_PIN_PWM,IGN2_PIN_DIG); 

    igniterMap.insert({IGN1_ID, Igniter1});
    igniterMap.insert({IGN2_ID, Igniter2});
    return true;
}

// Sets up the Valves on the Lower Engine Node
bool Rocket::initializeLowerValves() 
{
    Valve HP(HP_ID,HP_PIN_PWM,HP_PIN_DIG);      // High Press Valve
    Valve HV(HV_ID,HV_PIN_PWM,HV_PIN_DIG);      // High Vent Valve 
    Valve FMV(FMV_ID,FMV_PIN_PWM,FMV_PIN_DIG);  // Fuel Main Valve
    Valve LMV(LMV_ID,LMV_PIN_PWM,LMV_PIN_DIG);  // Lox Main Valve

    valveMap[HP_ID] =  HP;
    valveMap[HV_ID] = HV;
    valveMap[FMV_ID] = FMV;
    valveMap[LMV_ID] = LMV;
    return true;
}

// Sets up the Valves on the Upper Prop Node
bool Rocket::initializeUpperValves() 
{
    Valve LV(LV_ID,LV_PIN_PWM,LV_PIN_DIG);      // Lox Vent Valve
    Valve LDV(LDV_ID,LDV_PIN_PWM,LDV_PIN_DIG);  // Lox Dome Vent Valve
    Valve LDR(LDR_ID,LDR_PIN_PWM,LDR_PIN_DIG);  // Lox Dome Reg Valve
    Valve FV(FV_ID,FV_PIN_PWM,FV_PIN_DIG);      // Fuel Vent Valve
    Valve FDV(FDV_ID,FDV_PIN_PWM,FDV_PIN_DIG);  // Fuel Dome Vent Valve
    Valve FDR(FDR_ID,FDR_PIN_PWM,FDR_PIN_DIG);  // Fuel Dome Reg Valve

    valveMap.insert({LV_ID, LV});
    valveMap.insert({LDV_ID, LDV});
    valveMap.insert({LDR_ID, LDR});
    valveMap.insert({FV_ID, FV});
    valveMap.insert({FDV_ID, FDV});
    valveMap.insert({FDR_ID, FDR});
    return true;
}

// Sets up the Sensors on the Upper Prop Node
bool Rocket::initializeUpperSensors() 
{
    sensorMap.insert({PT_LOX_HIGH_ID, Sensor(PT_LOX_HIGH_ID, PT_LOX_HIGH_PIN, PT_LOX_HIGH_CAL_M, PT_LOX_HIGH_CAL_B)});
    sensorMap.insert({PT_FUEL_HIGH_ID, Sensor(PT_FUEL_HIGH_ID, PT_FUEL_HIGH_PIN, PT_FUEL_HIGH_CAL_M, PT_FUEL_HIGH_CAL_B)});
    sensorMap.insert({PT_LOX_DOME_ID, Sensor(PT_LOX_DOME_ID, PT_LOX_DOME_PIN, PT_LOX_DOME_CAL_M, PT_LOX_DOME_CAL_B)});
    sensorMap.insert({PT_FUEL_DOME_ID, Sensor(PT_FUEL_DOME_ID, PT_FUEL_DOME_PIN, PT_FUEL_DOME_CAL_M, PT_FUEL_DOME_CAL_B)});
    sensorMap.insert({PT_LOX_TANK_1_ID, Sensor(PT_LOX_TANK_1_ID, PT_LOX_TANK_1_PIN, PT_LOX_TANK_1_CAL_M, PT_LOX_TANK_1_CAL_B)});
    sensorMap.insert({PT_LOX_TANK_2_ID, Sensor(PT_LOX_TANK_2_ID, PT_LOX_TANK_2_PIN, PT_LOX_TANK_2_CAL_M, PT_LOX_TANK_2_CAL_B),});
    sensorMap.insert({PT_FUEL_TANK_1_ID, Sensor(PT_FUEL_TANK_1_ID, PT_FUEL_TANK_1_PIN, PT_FUEL_TANK_1_CAL_M, PT_FUEL_TANK_1_CAL_M)});
    sensorMap.insert({PT_FUEL_TANK_2_ID, Sensor(PT_FUEL_TANK_2_ID, PT_FUEL_TANK_2_PIN, PT_FUEL_TANK_2_CAL_M, PT_FUEL_TANK_2_CAL_B)});
    return true;
}

// Sets up the Sensors on the Lower Engine Node
bool Rocket::initializeLowerSensors() 
{
    sensorMap.insert({PT_PNUEMATICS_ID, Sensor(PT_PNUEMATICS_ID, PT_PNUEMATICS_PIN, PT_PNUEMATICS_CAL_M, PT_PNUEMATICS_CAL_B)});
    sensorMap.insert({PT_LOX_INLET_ID, Sensor(PT_LOX_INLET_ID, PT_LOX_INLET_PIN, PT_LOX_INLET_CAL_M, PT_LOX_INLET_CAL_B)});
    sensorMap.insert({PT_FUEL_INLET_ID, Sensor(PT_FUEL_INLET_ID, PT_FUEL_INLET_PIN, PT_FUEL_INLET_CAL_M, PT_FUEL_INLET_CAL_B)});
    sensorMap.insert({PT_FUEL_INJECTOR_ID, Sensor(PT_FUEL_INJECTOR_ID, PT_FUEL_INJECTOR_PIN, PT_FUEL_INJECTOR_CAL_M, PT_FUEL_INJECTOR_CAL_B)});
    sensorMap.insert({PT_CHAMBER_1_ID, Sensor(PT_CHAMBER_1_ID, PT_CHAMBER_1_PIN, PT_CHAMBER_1_CAL_M, PT_CHAMBER_1_CAL_B)});
    sensorMap.insert({PT_CHAMBER_2_ID, Sensor(PT_CHAMBER_2_ID, PT_CHAMBER_2_PIN, PT_CHAMBER_2_CAL_M, PT_CHAMBER_2_CAL_B)});
    return true;
}

// Enabled testing features, but otherwise does nothing
bool Rocket::enterTest()
{
    currentState = Test;
    return true;
}

// Closes all valves and sets rocket for Standby
bool Rocket::enterStandby()
{
    setValvesOpen(false, (std::vector<int>){HP_ID, HV_ID, FMV_ID, LMV_ID, LV_ID, LDV_ID, LDR_ID, FV_ID, FDV_ID, FDR_ID});
    currentState = Standby;
    return true;
}

// Prepares rocket for HighPress
bool Rocket::enterHighPressArm()
{
    currentState = HighPressArm;
    return true;
}

// Opens High Press Valves
bool Rocket::enterHighPress()
{
    setValvesOpen(true, (std::vector<int>){HP_ID});
    currentState = HighPress;
    return true;
}

// Prepares rocket for TankPress
bool Rocket::enterTankPressArm()
{
    currentState = TankPressArm;
    return true;
}

// Opens LDR and FDR
bool Rocket::enterTankPress()
{
    setValvesOpen(true, (std::vector<int>){LDR_ID, FDR_ID});
    currentState = HighPress;
    return true;
}

// Prepares rocket for TankPress
bool Rocket::enterFireArm()
{
    currentState = FireArm;
    return true;
}

//TODO: Add igniter timings and countdown
bool Rocket::enterFire()
{
    //TODO ***************************************************************************** TODO
    currentState = Fire;
    return true;
}

// Opens all Vent valves and closes all other valves
bool Rocket::enterVent()
{
    setValvesOpen(true, (std::vector<int>){LV_ID, LDV_ID, HV_ID, FV_ID, FDV_ID});
    setValvesOpen(false, (std::vector<int>){HP_ID, LMV_ID, LDR_ID, FMV_ID, FDR_ID});
    currentState = Vent;
    return true;
}

// Closes all valves and aborts
bool Rocket::enterAbort()
{
    setValvesOpen(false, (std::vector<int>){HP_ID, HV_ID, FMV_ID, LMV_ID, LV_ID, LDV_ID, LDR_ID, FV_ID, FDV_ID, FDR_ID});
    currentState = Abort;
    return true;
}

// Opens given list of valves iff the valve exists on this rocket node
void Rocket::setValvesOpen(bool valvesOpenInput, const std::vector<int> &valveIDs)
{
    std::map<int,Valve>::iterator it;
    for(int valveID : valveIDs)
    {
        it = valveMap.find(valveID);
        if(it != valveMap.end())
            it->second.setValveOpen(valvesOpenInput);
    }
}