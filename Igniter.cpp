#include "Igniter.h"
#include "ExtendedIO.h"
#include <iostream>


// Getters
int Igniter::getID() {
    return this->id;
}

int Igniter::getPinPWM() {
    return this->pinPWM;
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
    /*Sets the state of Igniter Objects: True (Open) | False (Close)
    Returns true if successful*/

    ExtendedIO::pinModeExtended(this->pinDigital,1,OUTPUT); // Sets Pinmode to GPIO, Data Direction OUTPUT
    pinMode(this->pinPWM,OUTPUT);

    if(isignitionOn == true){
        ExtendedIO::digitalWriteExtended(this->pinDigital,1);
        digitalWrite(this->pinPWM,1);
        return true;
    }
    if(isignitionOn == false){
        ExtendedIO::digitalWriteExtended(this->pinDigital,0);
        digitalWrite(this->pinPWM,0);
        return false;
    }
}
