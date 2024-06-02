#include "Igniter.h"
#include "ExtendedIO.h"
#include <iostream>


Igniter::Igniter(): id(0), pinPWM(0), pinDigital(0), igniterOn(false) {
    pinMode(pinDigital, 1);
};
Igniter::Igniter(int id, int pinPWM, int pinDigital)
    : id(id), pinPWM(pinPWM), pinDigital(pinDigital), igniterOn(false) {
    pinMode(pinDigital, 1); 
    digitalWrite(this->pinDigital, 1);   
    }

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
    this->igniterOn = isignitionOn;
    pinMode(this->pinDigital,OUTPUT); // Sets Pinmode to GPIO, Data Direction OUTPUT
    //pinMode(this->pinPWM,OUTPUT);

    if(isignitionOn == true){
        digitalWrite(this->pinDigital,1);
        //digitalWrite(this->pinPWM,1);
        return true;
    }
    if(isignitionOn == false){
        digitalWrite(this->pinDigital,0);
        //digitalWrite(this->pinPWM,0);
        return false;
    }
}
