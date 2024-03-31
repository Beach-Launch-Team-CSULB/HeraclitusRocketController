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
#include "Config.h"



enum E_RocketState {Standby, HighPressArm, HighPress, TankPressArm, TankPress, FireArm, Fire,/* Vent, Abort,*/ Test};

class Rocket{ 
    public:
        E_RocketState currentState;
        std::map<int, Igniter> igniterMap;
        const int igniterIDArray[IGNITER_ARRAY_LENGTH] = IGNITER_ARRAY;

        std::map<int, Valve> valveMap;
        const int valveIDArray[VALVE_ARRAY_LENGTH] = VALVE_ARRAY;

        std::map<int, Sensor> sensorMap;
        const int sensorIDArray[SENSOR_ARRAY_LENGTH] = SENSOR_ARRAY;

        //const std::vector<int> &sensorIDVector;
        LEDController ledArray;

        // Constructor 
        Rocket();

        // Output 
        //float sensorRead(Sensor);
        float sensorRead(int);
        bool ignitionRead(int);
        bool valveRead(int);
        void pollSensors();
        
        // Commands 
        bool setIgnitionOn(int,bool);
        bool setValveOn(int,bool);
        void setLED(int ledID, Color newColor);

        bool enterState(E_RocketState stateToEnter); 
        bool vent();
        bool abort();

        // Execution Check
        bool getExecuting();

        bool canEnterState(E_RocketState stateToEnter); 
    
   private: 
        VehicleState state;
        bool executingCommand;
        //int ALARA; // 0 = Lower , 1 = Upper  
       
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

};

#endif
