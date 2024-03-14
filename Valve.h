#ifndef VALVE_H
#define VALVE_H
#include <Arduino.h>

class Valve{ 
    private: 
        int id;
        int pinPMW;
        int pinDigital;
        bool valveOpen;

    public:
        Valve(int id, int pinPMW, int pinDigital) 
            : id(id), pinPMW(pinPMW), pinDigital(pinDigital), valveOpen(false) {}
        int getID();
        int getPinPMW();
        int getPinDigital();
        bool getValveOpen();
        bool setPinDigital(int);
        bool setValveOpen(bool);
};

#endif
