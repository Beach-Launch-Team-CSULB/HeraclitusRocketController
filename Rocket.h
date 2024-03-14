#ifndef ROCKET_H
#define ROCKET_H 

#include <Arduino.h>
#include <IntervalTimer.h>
#include <map>
#include "VehicleState.h"

class Rocket{ 
    private: 
        VehicleState state;
        bool executingCommand;
        int ALARA;                      // 0 = Lower , 1 = Upper  
        std::map<int, Igniter> igniterMap;
        std::map<int, Valve> valveMap;
        std::map<int, Sensor> sensorMap;

    public:
        // Constructor 
        Rocket(int ALARA) : ALARA(ALARA){}

        // Output 
        int sensorRead(int);
        bool ignitionRead(int);
        bool valveRead(int);
        
        // Commands 
        bool setIgnitionOn(int,bool);
        bool setValveOn(int,bool);

        // Execution Check
        bool getExecuting();
    
   private:
        bool initializeIgniters();
        bool initializeUpperValves();
        bool initializeLowerValves();
        bool initializeSensors();
      
        
};

#endif
