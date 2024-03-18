#include "Valve.h"
#include "ExtendedIO.h"

    // Constructor
    Valve::Valve(int id, int pinPWM, int pinDigital) 
        : id(id), pinPWM(pinPWM), pinDigital(pinDigital), valveOpen(false) {}


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
        /*Sets the state of Valve Objet: True (Open) | False (Close)
        Returns true if successful*/
        
        ExtendedIO::pinModeExtended(this->pinDigital,1,OUTPUT);     // Sets Manual Pinmode to GPIO, Data Direction OUTPUT
        pinMode(this->pinPWM,1);

        if(ValveOpenInput == true){
            ExtendedIO::digitalWriteExtended(this->pinDigital,1); 
            analogWrite(this->pinPWM,256);
            return true;
        }
        if(ValveOpenInput == false){
            ExtendedIO::digitalWriteExtended(this->pinDigital,0);
            digitalWrite(this->pinPWM,256);
            return true;
        }
        return false;
        
    }


