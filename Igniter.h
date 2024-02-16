#ifndef IGNITER_H
#define IGNITER_H
#include <Arduino.h>

class Igniter{ 
    private: 
        int id;
        int pinID;
        int pinDigital;
        int pinPWM;
        bool igniterOn;
        bool defaultStateOn;
    public:
        Igniter(int id, int pinID, int pinDigital, int pinPWM, bool igniterOn, bool defaultStateOn);
        int getID();
        int getPinID();
        int getPinDigital();
        int getPinPWM();
        bool getIgniterOn();
        bool setPinDigital(int);
        bool setPinPWM(int);
        bool setIgniterOn(bool);
};

#endif