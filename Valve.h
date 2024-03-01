#ifndef VALVE_H
#define VALVE_H
#include <Arduino.h>

class Valve{ 
    private: 
        int id;
        int pinID;
        int pinDigital;
        bool valveOpen;

    public:
        Valve(int id, int pinID, int pinDigital) 
            : id(id), pinID(pinID), pinDigital(pinDigital), valveOpen(false) {}
        int getID();
        int getPinID();
        int getPinDigital();
        bool getValveOpen();
        bool setPinDigital(int);
        bool setValveOpen(bool);
};

#endif
