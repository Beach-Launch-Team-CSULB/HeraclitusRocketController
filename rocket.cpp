#include <iostream>
#include <map>
#include <utility>
#include "Rocket.h"
#include "Valve.h"
#include "Igniter.h"
#include "Sensor.h"
#include "PressureTransducer.h"
#include "Config.h"
#include <ADC.h>


void Rocket::setLED(int ledID, Color newColor){
    allOfTheLights.setLed(ledID, newColor);
}

// Constructor definition
Rocket::Rocket(int ALARA){
    if (ALARA == 0){                             // Lower ALARA Setup 
        initializeIgniters();
        initializeLowerValves();
        initializeLowerSensors();
    }
    if (ALARA == 1){                             // Upper ALARA Setup
        initializeUpperValves();
        initializeUpperSensors();
    }
    //allOfTheLights.init();
    //TJ 4/12 changed state map WIP*****
    // 4/13:
                                          // Abort, Vent, Fire, Tank Press, High Press, Standby, Ignite, Test 
                                           //  A    V    F    TP    H    S    I    TE 
    stateMap.emplace(HP_ID,   std::vector<int>{0,   0,   1,   1,    1,   0,   1,   0});
    stateMap.emplace(HV_ID,   std::vector<int>{0,   1,   0,   0,    0,   0,   0,   0});
    stateMap.emplace(LV_ID,   std::vector<int>{0,   1,   0,   0,    0,   0,   0,   0});
    stateMap.emplace(LMV_ID,  std::vector<int>{0,   0,   0,   0,    0,   0,   0,   0});
    stateMap.emplace(LDR_ID,  std::vector<int>{0,   0,   1,   1,    0,   0,   1,   0});
    stateMap.emplace(LDV_ID,  std::vector<int>{0,   1,   0,   0,    0,   0,   0,   0});
    stateMap.emplace(FV_ID,   std::vector<int>{0,   1,   0,   0,    0,   0,   0,   0});
    stateMap.emplace(FMV_ID,  std::vector<int>{0,   0,   0,   0,    0,   0,   0,   0});
    stateMap.emplace(FDR_ID,  std::vector<int>{0,   0,   1,   1,    0,   0,   1,   0});
    stateMap.emplace(FDV_ID,  std::vector<int>{0,   1,   0,   0,    0,   0,   0,   0});
    stateMap.emplace(IGN1_ID, std::vector<int>{0,   0,   1,   0,    0,   0,   1,   0});
    stateMap.emplace(IGN2_ID, std::vector<int>{0,   0,   1,   0,    0,   0,   1,   0});

    LEDstateMap.emplace(LED0,    std::vector<Color>{GREEN, PURPLE, RED, ORANGE, ORANGE, WHITE, ORANGE, GREEN});
    LEDstateMap.emplace(LED1,    std::vector<Color>{PURPLE, PURPLE, RED, GREEN, BLUE, WHITE, ORANGE, GREEN});

    // Begins in the Test state
    changeState(STANDBY);
    manualVent = false;
}

/*float Rocket::sensorRead(Sensor sensor) {
    return sensor.readDataRaw();
}*/

float Rocket::sensorRead(int sensorId, ADC &adc) {
    // 4/15: After we get this working - check how many times it is logging.
    // It may be worth creating a vector that contains global variables and is updated by the CANDriver.
    //return sensorMap[sensorId].getCurrentValue() * sensorMap[sensorId].getCalibrationSlope() - sensorMap[sensorId].getCalibrationIntercept();
    return sensorMap[sensorId].readDataRaw(adc);
    //return sensorMap[sensorId].getCurrentValue(adc);
}

bool Rocket::ignitionRead(int igniterID) {
    return igniterMap[igniterID].getIgniterOn();
}

bool Rocket::valveRead(int valveID) {
    return valveMap[valveID].getValveOpen();
}

bool Rocket::setIgnitionOn(int igniterID, bool ignitionOn) {
    return igniterMap[igniterID].setIgniterOn(ignitionOn);
}

bool Rocket::setValveOn(int valveID, bool valveOpen) {
    return valveMap[valveID].setValveOpen(valveOpen);
}

void Rocket::calibrateSensor(int sensorId, bool isM, float val) {
    if (isM) sensorMap[sensorId].setCalibrationParametersM(val);
    else sensorMap[sensorId].setCalibrationParametersB(val);
}

float Rocket::getSensorCalibration(int sensorId, bool isM) {
    if (isM) sensorMap[sensorId].getCalibrationSlope();
    else sensorMap[sensorId].getCalibrationIntercept(); 
}

bool Rocket::changeState(int state) {
    for (std::map<int,Valve>::iterator valve = valveMap.begin(); valve != valveMap.end(); ++valve) {
        setValveOn(valve->first, stateMap[valve->first][state]);
    }
    for (std::map<int,Igniter>::iterator Igniter = igniterMap.begin(); Igniter != igniterMap.end(); ++Igniter) {
        setIgnitionOn(Igniter->first, stateMap[Igniter->first][state]);
    }


    // 4/14:*************************************
    //setLED(LED0, LEDstateMap[LED0][state]);
    //allOfTheLights.setLed(LED1, LEDstateMap[LED1][state]);
    //*******************************************

    this->state = state;
    Serial.println(state);
    return true;
}

bool Rocket::getExecuting(){
    return this->executingCommand;
}

bool Rocket::getManualVent() {
    return this->manualVent;
}

void Rocket::setManualVent(bool isEnabled) {
    this->manualVent = isEnabled;
}

// 4/8/'24
uint8_t Rocket::getState() {
    return this->state;
}


bool Rocket::initializeIgniters(){
    
    Igniter Igniter1(IGN1_ID, IGN1_PIN_PWM,IGN1_PIN_DIG);
    //Igniter Igniter2(IGN2_ID, IGN2_PIN_PWM,IGN2_PIN_DIG); 


    igniterMap.insert({IGN1_ID, Igniter1});
    //igniterMap.insert({IGN2_ID, Igniter2});

    return true;
}

bool Rocket::initializeLowerValves(){
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

bool Rocket::initializeUpperValves(){
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

bool Rocket::initializeUpperSensors()
{
    
    sensorMap.insert({PT_LOX_HIGH_ID, Sensor(PT_LOX_HIGH_ID, PT_LOX_HIGH_PIN, PT_LOX_HIGH_CAL_M, PT_LOX_HIGH_CAL_B)});
    sensorMap.insert({PT_FUEL_HIGH_ID, Sensor(PT_FUEL_HIGH_ID, PT_FUEL_HIGH_PIN, PT_FUEL_HIGH_CAL_M, PT_FUEL_HIGH_CAL_B)});
    sensorMap.insert({PT_LOX_DOME_ID, Sensor(PT_LOX_DOME_ID, PT_LOX_DOME_PIN, PT_LOX_DOME_CAL_M, PT_LOX_DOME_CAL_B)});
    sensorMap.insert({PT_FUEL_DOME_ID, Sensor(PT_FUEL_DOME_ID, PT_FUEL_DOME_PIN, PT_FUEL_DOME_CAL_M, PT_FUEL_DOME_CAL_B)});
    sensorMap.insert({PT_LOX_TANK_1_ID, Sensor(PT_LOX_TANK_1_ID, PT_LOX_TANK_1_PIN, PT_LOX_TANK_1_CAL_M, PT_LOX_TANK_1_CAL_B)});
    sensorMap.insert({PT_LOX_TANK_2_ID, Sensor(PT_LOX_TANK_2_ID, PT_LOX_TANK_2_PIN, PT_LOX_TANK_2_CAL_M, PT_LOX_TANK_2_CAL_B),});
    sensorMap.insert({PT_FUEL_TANK_1_ID, Sensor(PT_FUEL_TANK_1_ID, PT_FUEL_TANK_1_PIN, PT_FUEL_TANK_1_CAL_M, PT_FUEL_TANK_1_CAL_B)});
    sensorMap.insert({PT_FUEL_TANK_2_ID, Sensor(PT_FUEL_TANK_2_ID, PT_FUEL_TANK_2_PIN, PT_FUEL_TANK_2_CAL_M, PT_FUEL_TANK_2_CAL_B)});
    

    return true;
}

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

// 4/14: New attempt
void Rocket::zeroSensors(int node)
{
    if(node == 1)
    {
        // ******* 4/15: Put this back to how it was before. Right now - this works - but I was initially using the sensor class
        // and not global variables. I messed something up in the main logic and the function was not getting called correctly.
        // Propulsion Node
        /*zeroPTOne   = sensorRead(PT_LOX_HIGH_ID);
        zeroPTTwo   = sensorRead(PT_FUEL_HIGH_ID);
        zeroPTThree = sensorRead(PT_LOX_DOME_ID);
        zeroPTFour  = sensorRead(PT_FUEL_DOME_ID);

        zeroPTFive  = sensorRead(PT_LOX_TANK_1_ID);
        zeroPTSix   = sensorRead(PT_LOX_TANK_2_ID);
        zeroPTSeven = sensorRead(PT_FUEL_TANK_1_ID);
        zeroPTEight = sensorRead(PT_FUEL_TANK_2_ID);
    }
    else
    {
        // Engine Node
        zeroPTOne   = sensorRead(PT_PNUEMATICS_ID);
        zeroPTTwo   = sensorRead(PT_LOX_INLET_ID);
        zeroPTThree = sensorRead(PT_FUEL_INLET_ID);
        zeroPTFour  = sensorRead(PT_FUEL_INJECTOR_ID);

        zeroPTFive  = sensorRead(PT_CHAMBER_1_ID);
        zeroPTSix   = sensorRead(PT_CHAMBER_2_ID);*/
    }
}

