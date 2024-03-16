#include "Valve.h"
#include "ExtendedIO.h"

    // Getters
    int Valve::getID() {
        return this->id;
    }

    int Valve::getPinPWM() {
        return this->pinPWM;
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
            ExtendedIO::digitalWriteExtended(this->pinDigital,1); 
            digitalWrite(this->pinPWM,1);
            return true;
        }
        if(ValveOpenInput == false){
            ExtendedIO::digitalWriteExtended(this->pinDigital,0);
            digitalWrite(this->pinPWM,0);
            return true;
        }
        return false;
        
    }


