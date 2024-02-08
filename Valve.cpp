#ifndef VALVE_H
#define VALVE_H
#include <Arduino.h>

class Valve{ 
  #include "valve.h"

    // Constructor
    Valve::Valve(int id, int pinID, int pinDigital, int pinPWM) {
        // Initialize member variables
        this->id = id;
        this->pinID = pinID;
        this->pinDigital = pinDigital;
        this->pinPWM = pinPWM;
        this->valveOpen = false; // Assuming valve starts closed by default
    }

    // Getters
    int Valve::getID() {
        //code here
    }

    int Valve::getPinID() {
        //code here
    }

    int Valve::getPinDigital() {
        //code here
    }

    int Valve::getPinPWM() {
        //code here
    }

    bool Valve::getValveOpen() {
        //code here
    }

    // Setters
    int Valve::setPinDigital() {
        //code here
    }

    int Valve::setPinPWM() {
        //code here
    }

    int Valve::setValveOpen() {
        //code here
    }

};

#endif
