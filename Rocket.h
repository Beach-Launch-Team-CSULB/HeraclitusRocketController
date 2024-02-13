#ifndef ROCKET_H
#define ROCKET_H 

#include <Arduino.h>
#include <VehicleState.h>
#include <IntervalTimer.h>

class Rocket{ 
    public: 
        IntervalTimer sensorTimer;
        IntervalTimer launchTimer; 
        VehicleState state;
        bool executingCommand;
        int sensorRead(int);
        int ignitionRead(int);
        int valveRead(int);
        int toggleIgnition(int);
        int toggleValue(int);
        
};

#endif
