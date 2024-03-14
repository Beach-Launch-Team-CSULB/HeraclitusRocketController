#ifndef PRESSURE_TRANSDUCER_H
#define PRESSURE_TRANSDUCER_H

#include "Sensor.hpp"
#include <Arduino.h>

class LoadCell : public Sensor {

    public:
        // Using Sensor's constructor initialization list
        LoadCell(int label, int pin, float min, float max, float offset = 0.0f)
        : Sensor(label, pin, min, max, offset) {}

        virtual ~LoadCell() {}

};

#endif // PRESSURE_TRANSDUCER_H
