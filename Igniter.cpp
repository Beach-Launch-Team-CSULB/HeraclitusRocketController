#include "Igniter.h"
#include <iostream>

//constructor
Igniter::Igniter(int id, int pinID, int pinDigital, int pinPWM, bool igniterOn) {
    this->id = id;
    this->pinID = pinID;
    this->pinDigital = pinDigital;
    this->pinPWM = pinPWM;
    this->igniterOn = igniterOn;
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
int Igniter::setPinDigital() {
    //code here
}

int Igniter::setPinPWM() {
    //code here
}

int Igniter::setIgniterOn() {
    //code here
}

