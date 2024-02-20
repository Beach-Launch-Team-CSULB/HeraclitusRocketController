#include <Valve.h>

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
        return this->id;
    }

    int Valve::getPinID() {
        return this->pinID;
    }

    int Valve::getPinDigital() {
        return this->pinDigital;
    }

    int Valve::getPinPWM() {
        return this->pinPWM;
    }

    bool Valve::getValveOpen() {
        return this->valveOpen;
    }

    // Setters
    bool Valve::setPinDigital(int newPinDigital) {
        this->pinDigital = newPinDigital;
        if(this->pinDigital == newPinDigital){
            return true;
        }
        else {return false;}
    }

    bool Valve::setPinPWM(int newPWMPin) {
        //code here
    }

    bool Valve::setValveOpen(bool ValveOpenInput) {
        if(ValveOpenInput == true){
            digitalWrite(this->pinDigital,1);
            digitalWrite(this->pinPWM,1);
            return true;
        }
        if(ValveOpenInput == false){
            digitalWrite(this->pinDigital,0);
            digitalWrite(this->pinPWM,0);
            return true;
        }
    }


