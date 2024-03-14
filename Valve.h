#ifndef VALVE_H
#define VALVE_H
#include <Arduino.h>

class Valve{ 
    private: 
        int id;
        int pinPWM;
        int pinDigital;
        bool valveOpen;

    public:
        Valve(int id, int pinPWM, int pinDigital) 
            : id(id), pinPWM(pinPWM), pinDigital(pinDigital), valveOpen(false) {}
        int getID();
        int getPinPWM();
        int getPinDigital();
        bool getValveOpen();
        bool setPinDigital(int);
        bool setValveOpen(bool);
};

#endif
