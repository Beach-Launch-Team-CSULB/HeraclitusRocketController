#ifndef VALVE_H
#define VALVE_H
#include <Arduino.h>

class Valve{ 
    private: 
        int id;
        int pinID;
        int pinDigital;
        int pinPWM;
        bool valveOpen;
    public:
        Valve(int id, int pinID, int pinDigital, int pinPWM);
        int getID();
        int getPinID();
        int getPinDigital();
        int getPinPWM();
        bool getValveOpen();
        int setPinDigital();
        int setPinPWM();
        int setValveOpen();
};

#endif
