#ifndef PRESSURE_TRANSDUCER_H
#define PRESSURE_TRANSDUCER_H

#include "Sensor.h" // Ensure this includes the path to the Sensor base class
#include <Arduino.h> // For hardware interfacing functions

class PressureTransducer : public Sensor {

    public:
        // Using Sensor's constructor initialization list
        PressureTransducer(int label, int pin, float min, float max, float offset = 0.0f)
        : Sensor(label, pin, min, max, offset) {}

        virtual ~PressureTransducer() {}

};

#endif // PRESSURE_TRANSDUCER_H
