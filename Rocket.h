#ifndef ROCKET_H
#define ROCKET_H 

#include <Arduino.h>
#include <map>
#include <utility>
#include "Igniter.h"
#include "Valve.h"
#include "Sensor.h"
#include <vector>
#include "LEDController.h"
#include <ADC.h>


class Rocket{ 
    public:

        std::map<int, Igniter> igniterMap;
        std::map<int, Valve> valveMap;
        std::map<int, Sensor> sensorMap;
        //std::map<int, int[8]> stateMap;
        // 4/9/2024
        std::map<int, std::vector<int> > stateMap;
        std::map<int, std::vector<Color>> LEDstateMap;
        LEDController allOfTheLights;



        //int sensorArray[8];
        

        // Constructor 
        Rocket(int ALARA);

        // Output 
        //float sensorRead(Sensor);
        float sensorRead(int, ADC &adc);
        bool ignitionRead(int);
        bool valveRead(int);
       // int getState();

        // 4/9/2024
        uint8_t getState();
        void zeroSensors(int node); // 4/11/2024
        void calibrateSensor(int sensorId, bool isM, float val);
        void getSensorCalibration(int sensorId, bool isM);
        
        // Commands 
        bool setIgnitionOn(int,bool);
        bool setValveOn(int,bool);
        void setLED(int, Color);
        bool changeState(int);

        // Execution Check
        bool getExecuting();

        bool getManualVent();
        void setManualVent(bool);

    
   private: 
        int state;
        bool executingCommand;
        int ALARA;                      // 0 = Lower , 1 = Upper  
        bool manualVent;

        //Sensor* sensorArray[8];
        bool initializeIgniters();
        bool initializeUpperValves();
        bool initializeLowerValves();
        bool initializeUpperSensors();
        bool initializeLowerSensors();
    
};

#endif
