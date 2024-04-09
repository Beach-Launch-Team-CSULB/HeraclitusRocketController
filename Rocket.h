#ifndef ROCKET_H
#define ROCKET_H 

#include <Arduino.h>
#include <map>
#include <utility>
#include "VehicleState.h"
#include "Igniter.h"
#include "Valve.h"
#include "Sensor.h"


class Rocket{ 
    public:

        std::map<int, Igniter> igniterMap;
        std::map<int, Valve> valveMap;
        std::map<int, Sensor> sensorMap;
        int sensorArray[8];

        // Constructor 
        Rocket(int ALARA);

        // Output 
        //float sensorRead(Sensor);
        float sensorRead(int);
        bool ignitionRead(int);
        bool valveRead(int);
        
        // Commands 
        bool setIgnitionOn(int,bool);
        bool setValveOn(int,bool);

        // Execution Check
        bool getExecuting();

        // Getter for Rocket's state
        uint8_t getState();
    
   private: 
        VehicleState state;
        bool executingCommand;
        int ALARA;                      // 0 = Lower , 1 = Upper  
       
        //Sensor* sensorArray[8];
        bool initializeIgniters();
        bool initializeUpperValves();
        bool initializeLowerValves();
        bool initializeUpperSensors();
        bool initializeLowerSensors();
    
};

#endif
