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


enum E_RocketState {Standby, HighPressArm, HighPress, TankPressArm, TankPress, FireArm, Fire, Vent, Abort, Test};

class Rocket{ 
    public:
        E_RocketState currentState;
        std::map<int, Igniter> igniterMap;
        std::map<int, Valve> valveMap;
        std::map<int, Sensor> sensorMap;

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

        bool enterState(E_RocketState stateToEnter); 
        bool canEnterState(E_RocketState stateToEnter); 
    
   private: 
        VehicleState state;
        bool executingCommand;
        int ALARA; // 0 = Lower , 1 = Upper  
       
        //Sensor* sensorArray[8];
        bool initializeIgniters();
        bool initializeUpperValves();
        bool initializeLowerValves();
        bool initializeUpperSensors();
        bool initializeLowerSensors();

        void setValvesOpen(bool valvesOpenInput, const std::vector<int> &valveIDs);

        //Called by enterState()
        bool enterTest();
        bool enterStandby();
        bool enterHighPressArm();
        bool enterHighPress();
        bool enterTankPressArm();
        bool enterTankPress();
        bool enterFireArm();
        bool enterFire();
        bool enterVent();
        bool enterAbort();
};

#endif
