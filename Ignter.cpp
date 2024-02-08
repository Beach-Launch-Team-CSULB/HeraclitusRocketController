#include "Igniter.h"
class Ignter{

//constructor
Igniter::Igniter(int id, int pinID, int pinDigital, int pinPWM) {
    this->id = id;
    this->pinID = pinID;
    this->pinDigital = pinDigital;
    this->pinPWM = pinPWM;
}

// Getters
int Igniter::getID() {
    //code here
}

int Igniter::getPinID() {
    //code here
}

int Igniter::getPinDigital() {
    //code here
}

int Igniter::getPinPWM() {
    //code here
}

bool Igniter::getIgniterOn() {
    //code here
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

}