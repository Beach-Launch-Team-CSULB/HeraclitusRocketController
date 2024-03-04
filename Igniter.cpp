#include "Igniter.h"
#include <iostream>


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
