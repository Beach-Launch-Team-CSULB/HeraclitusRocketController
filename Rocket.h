#ifndef ROCKET_H
#define ROCKET_H 

#include <Arduino.h>
#include <map>
#include <utility>
#include "VehicleState.h"
#include "Igniter.h"
#include "Valve.h"
#include "Sensor.h"
#include <vector>


class Rocket{ 
    public:

        std::map<int, Igniter> igniterMap;
        std::map<int, Valve> valveMap;
        std::map<int, Sensor> sensorMap;
        //std::map<int, int[8]> stateMap;
        // 4/9/2024
        std::map<int, std::vector<int> > stateMap;



        //int sensorArray[8];
        

        // Constructor 
        Rocket(int ALARA);

        // Output 
        //float sensorRead(Sensor);
        float sensorRead(int);
        bool ignitionRead(int);
        bool valveRead(int);
       // int getState();

        // 4/9/2024
        uint8_t getState();
        
        // Commands 
        bool setIgnitionOn(int,bool);
        bool setValveOn(int,bool);
        bool changeState(int);

        // Execution Check
        bool getExecuting();

    
   private: 
        int state;
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
