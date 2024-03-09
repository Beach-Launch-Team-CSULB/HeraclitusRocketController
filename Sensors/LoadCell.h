#ifndef PRESSURE_TRANSDUCER_H
#define PRESSURE_TRANSDUCER_H

#include "Sensor.h"
#include <Arduino.h>

class LoadCell : public Sensor {

    public:
        // Using Sensor's constructor initialization list
        LoadCell(int labelID, int pinID, float linCoM, float linCoB);

        //virtual ~LoadCell() {}

};

#endif // PRESSURE_TRANSDUCER_H
