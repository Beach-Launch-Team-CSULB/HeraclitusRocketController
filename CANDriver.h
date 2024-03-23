// 2/10/2024

#ifndef CANDRIVER_H
#define CANDRIVER_H

//#include <Arduino.h>
#include <FlexCAN.h>
#include <iostream>
#include <vector>
//#include <stdint.h>

#include "Config.h"
#include "Valve.h"
#include "Igniter.h"


class CANDriver 
{
    private:
        FlexCAN CANBus;                     // Is this necessary?
        std::vector<uint8_t> commands;
        
    public:
        
        // If we are able to set up the .begin and all that here within the CANDriver.cpp - that would be cool.
        // Otherwise it would probably need to happen in main.
        CANDriver();

        // Would be RocketState rocketState instead of uint8_t rocketState.
        void sendStateReport(int time, uint8_t rocketState, Valve valves[], Igniter igniters[], bool Prop);
        void sendSensorData(int sensorID, float sensorData1, float sensorData2, float SensorData3, float SensorData4);

        uint32_t readMessage();
        //^ .push_back() into commands vector

        //void sendOperatorMessage(int messageID);
};

#endif