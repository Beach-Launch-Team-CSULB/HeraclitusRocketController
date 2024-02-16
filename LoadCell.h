#ifndef PRESSURE_TRANSDUCER_H
#define PRESSURE_TRANSDUCER_H

#include "Sensor.h"
#include <Arduino.h>

class LoadCell : public Sensor {
    protected:
    uint32_t sampleRate; // Current sample rate

public:
    // Using Sensor's constructor initialization list
    LoadCell(int label, int pin, const std::string& unit, 
                       float min, float max, float offset = 0.0f)
    : Sensor(label, pin, unit, min, max, offset) {}

    virtual ~LoadCell() {}

    void setSampleRate(uint32_t rate) {
        sampleRate = rate;
    }

    void calibrate() {
        return;
    }
};

#endif // PRESSURE_TRANSDUCER_H
