#ifndef CANDRIVER_H
#define CANDRIVER_H

#include <FlexCAN.h>
#include Config.h

// struct data

class CANDriver {
    private:
        FlexCAN CANBus;
        // message queue, array of x length
        
    public:
        CANDriver();
        
        void packageValveIgniterData(); 
        void packageSensorData();
        void packageRocketState(); 
        void packageTimerData(); 
        void packageOperatorMessage();

        int readMessage();
};

#endif