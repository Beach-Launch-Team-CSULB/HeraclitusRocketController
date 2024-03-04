#ifndef IGNITER_H
#define IGNITER_H
#include <Arduino.h>

class Igniter{ 
    private: 
        int id;
        int pinID;
        int pinDigital;
        bool igniterOn;
        bool defaultStateOn;

    public:
        Igniter(int id, int pinID, int pinDigital)
            : id(id), pinID(pinID), pinDigital(pinDigital), igniterOn(false) {}
        int getID();
        int getPinID();
        int getPinDigital();
        bool getIgniterOn();
        bool setPinDigital(int);
        bool setPinPWM(int);
        bool setIgniterOn(bool);
};

#endif
