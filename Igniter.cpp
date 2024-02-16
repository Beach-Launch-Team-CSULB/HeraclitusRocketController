#include "Igniter.h"
#include <iostream>

//constructor
Igniter::Igniter(int id, int pinID, int pinDigital, int pinPWM, bool igniterOn, bool defaultStateOn) {
    this->id = id;
    this->pinID = pinID;
    this->pinDigital = pinDigital;
    this->pinPWM = pinPWM;
    this->igniterOn = igniterOn;
    this->defaultStateOn = defaultStateOn;
}

// Getters
int Igniter::getID() {
    return this->id;
}

int Igniter::getPinID() {
    return this->pinID;
}

int Igniter::getPinDigital() {
    return this->pinDigital;
}

int Igniter::getPinPWM() {
    return this->pinPWM;
}

bool Igniter::getIgniterOn() {
    return this->igniterOn;
}

// Setters
bool Igniter::setPinDigital(int pinDigital) {
    this->pinDigital = pinDigital;
}

bool Igniter::setPinPWM(int pinPWM) {
    //code here
    
}

bool Igniter::setIgniterOn(bool isignitionOn){
    //code here
    
}
