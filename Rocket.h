#ifndef ROCKET_H
#define ROCKET_H 

#include <Arduino.h>
#include <map>
#include <utility>
#include "VehicleState.h"
#include "Igniter.h"
#include "Valve.h"
#include "Sensor.h"
#include "LEDController.h"
#include <vector>


class Rocket{ 
    public:

        std::map<int, Igniter> igniterMap;
        std::map<int, Valve> valveMap;
        std::map<int, Sensor> sensorMap;
        //std::map<int, int[8]> stateMap;
        // 4/9/2024
        std::map<int, std::vector<int>> stateMap;
        LEDController ledController;

        //4/11/2024
        std::map<int, float> sensorZeroMap;



        

        // Constructor 
        Rocket(int ALARA);

        // Output 
        float sensorRead(int);
        bool ignitionRead(int);
        bool valveRead(int);
        uint8_t getState();
        
        // Commands 
        bool setIgnitionOn(int,bool);
        bool setValveOn(int,bool);
        bool changeState(int);
        //bool calibrateSensors(); 4/11
        void calibrateSensors(int node);

        // Execution Check
        bool getExecuting();

    
   private: 
        int state;
        bool executingCommand;
        int ALARA;                      // 0 = Lower , 1 = Upper  
    
        bool initializeIgniters();
        bool initializeUpperValves();
        bool initializeLowerValves();
        bool initializeUpperSensors();
        bool initializeLowerSensors();
};

#endif
