#ifndef IGNITER_H
#define IGNITER_H
#include <Arduino.h>

class Rocket{ 
    private: 
        int id;
        int pinID;
        int pinDigital;
        int pinPWM;
    public:
        int getID();
        int getPinID();
        int getPinDigital();
        int getPinPWM();
        bool getIgniterOn();
        int setPinDigital();
        int setPWM();
};

#endif
