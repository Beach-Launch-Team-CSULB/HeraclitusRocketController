#ifndef PRESSURE_TRANSDUCER_H
#define PRESSURE_TRANSDUCER_H

// 3/12/2024 Depreciated: See Trauma Response


#include "Sensor.h"
#include <Arduino.h>

class LoadCell : public Sensor {

    public:
        //Constructor used by rocketdriver
        LoadCell(int labelID, int pinID, float linCoM, float linCoB);

        //Constructor used for uncalibrated sensors
        LoadCell(int labelID, int pinID);

};

#endif // PRESSURE_TRANSDUCER_H
