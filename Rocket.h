#ifndef ROCKET_H
#define ROCKET_H 

#include <Arduino.h>
#include <VehicleState.h>
#include <IntervalTimer.h>

class Rocket{ 
    public: 
        VehicleState state;
        bool executingCommand;

        int sensorRead(int);
        int ignitionRead(int);
        int valveRead(int);

        int setIgnitionOn(int);
        int setValveOn(int);

        int getExecuting(bool);
    private:
        bool createValve(int);
        bool createIgnition(int);
        bool createSensor(int);
        
};

#endif
