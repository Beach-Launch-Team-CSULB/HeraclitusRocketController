#include "Valve.h"
#include "ExtendedIO.h"

    // Constructor
    Valve::Valve(int id, int pinPWM, int pinDigital) 
        : id(id), pinPWM(pinPWM), pinDigital(pinDigital), valveOpen(false)
        {
            ExtendedIO::pinModeExtended(this->pinDigital, 1, OUTPUT); // Sets Manual Pinmode to GPIO, Data Direction OUTPUT
            pinMode(this->pinPWM, OUTPUT); //Teensy function to set up the PWM pin
        }


    // Getters
    int Valve::getID() {
        return this->id; }
    int Valve::getPinPWM() {
        return this->pinPWM; }
    int Valve::getPinDigital() {
        return this->pinDigital; }
    bool Valve::getValveOpen() {
        return this->valveOpen; }

    // Setter for digital pin address (probably don't use this. each valve should be initialized with its proper pin)
    bool Valve::setPinDigital(int newPinDigital)
    {
        this->pinDigital = newPinDigital;
        if(this->pinDigital == newPinDigital){
            return true;
        }
        return false;
    }

        /*Sets the state of Valve Objet: True (Open) | False (Close)
                Returns true if successful*/
    bool Valve::setValveOpen(bool valveOpenInput)
    {    
        // These should be initialized earlier and not called again, but having them in main did not work.

        // Try/Catch block was not working with our platformio.ini settings. This is untested -Aurum 3/20/2024
        this->valveOpen = valveOpenInput;
        ExtendedIO::digitalWriteExtended(this->pinDigital, valveOpenInput); 
        digitalWrite(this->pinPWM, valveOpenInput);        
        return true;
    }


