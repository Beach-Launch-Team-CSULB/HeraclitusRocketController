#include "Valve.h"

    // Getters
    int Valve::getID() {
        return this->id;
    }

    int Valve::getPinPMW() {
        return this->pinPMW;
    }

    int Valve::getPinDigital() {
        return this->pinDigital;
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
        return false;
    }

    bool Valve::setValveOpen(bool ValveOpenInput) {
        if(ValveOpenInput == true){
            digitalWrite(this->pinDigital,1);
            return true;
        }
        if(ValveOpenInput == false){
            digitalWrite(this->pinDigital,0);
            return true;
        }
        return false;
        
    }


