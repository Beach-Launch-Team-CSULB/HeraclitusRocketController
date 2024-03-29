#ifndef IGNITER_H
#define IGNITER_H
#include <Arduino.h>


class Igniter{ 
    private: 
        int id;
        int pinPWM;
        int pinDigital;
        bool igniterOn;
        bool defaultStateOn;

    public:
        Igniter()
            : id(0), pinPWM(0), pinDigital(0), igniterOn(false) {};
        Igniter(int id, int pinPWM, int pinDigital)
            : id(id), pinPWM(pinPWM), pinDigital(pinDigital), igniterOn(false) {}
        int getID();
        int getPinDigital();
        int getPinPWM();
        bool getIgniterOn();
        bool setPinDigital(int);
        bool setPinPWM(int);
        bool setIgniterOn(bool);
};

#endif
