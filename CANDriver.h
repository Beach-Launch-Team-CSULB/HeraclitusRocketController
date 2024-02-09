#ifndef CANDRIVER_H
#define CANDRIVER_H

#include <FlexCAN.h>
#include Config.h

class CANDriver {
    private:
        FlexCAN CANBus;
        //mstStruct msgReadQueue[20]; // Not a ring buffer
        void writeMessage();
        
    public:
        CANDriver();
        
        void sendValveIgniterData(int* valves[], int NUM_VALVES, int NUM_IGNITERS); 
        void sendSensorData(int sensorID, float sensorData);
        void sendRocketState(VehicleState rocketState); 
        void sendTimerData(int timerReading); 
        void sendOperatorMessage(int messageID);

        int readMessage();
};

#endif