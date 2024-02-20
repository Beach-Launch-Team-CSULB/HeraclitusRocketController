#ifndef ROCKET_H
#define ROCKET_H 

#include <Arduino.h>
#include <VehicleState.h>
#include <IntervalTimer.h>

class Rocket{ 

    public:
        // Internal Variables 
        VehicleState state;
        bool executingCommand;

        // Output 
        int sensorRead(int);
        bool ignitionRead(int);
        bool valveRead(int);
        
        // Commands 
        bool setIgnitionOn(int,bool);
        bool setValveOn(int,bool);

        // Execution Check
        bool getExecuting();
    
   
        
};

#endif
