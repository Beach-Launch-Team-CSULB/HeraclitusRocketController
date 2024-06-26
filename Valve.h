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
        Valve():
            id(0), pinPWM(0), pinDigital(0), valveOpen(false) {};
        Valve(int id, int pinPWM, int pinDigital);
        int getID();
        int getPinPWM();
        int getPinDigital();
        bool getValveOpen();
        bool setPinDigital(int);
        bool setValveOpen(bool);
};

#endif

