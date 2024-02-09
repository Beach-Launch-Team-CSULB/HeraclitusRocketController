#ifndef IGNITER_H
#define IGNITER_H
#include <Arduino.h>

class Igniter{ 
    private: 
        int id;
        int pinID;
        int pinDigital;
        int pinPWM;
    public:
        Igniter(int id, int pinID, int pinDigital, int pinPWM);
        int getID();
        int getPinID();
        int getPinDigital();
        int getPinPWM();
        bool getIgniterOn();
        int setPinDigital();
        int setPinPWM();
        int setIgniterOn();
};

#endif
