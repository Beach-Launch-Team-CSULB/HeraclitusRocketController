#include "Igniter.h"
#include <iostream>

//constructor
Igniter::Igniter(int id, int pinID, int pinDigital) {
    this->id = id;
    this->pinID = pinID;
    this->pinDigital = pinDigital;
    //this->pinPWM = pinPWM;
    this->igniterOn = false;
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
/*
int Igniter::getPinPWM() {
    return this->pinPWM;
}*/

bool Igniter::getIgniterOn() {
    return this->igniterOn;
}

// Setters
bool Igniter::setPinDigital(int newPinDigital) {
    this->pinDigital = newPinDigital;
    if(this->pinDigital == newPinDigital){
        return true;
    }
    else {return false;}
}

/*
bool Igniter::setPinPWM(int newPinPWM) {
    this->pinDigital = newPinPWM;
    if(this->pinDigital == newPinPWM){
        return true;
    }
    else {return false;}
}*/

bool Igniter::setIgniterOn(bool isignitionOn){
    if(isignitionOn == true){
        digitalWrite(this->pinDigital,1);
        return true;
    }
    if(isignitionOn == false){
        digitalWrite(this->pinDigital,0);
        return true;
    }
}

