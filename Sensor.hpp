#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>


class Sensor {
private:
    int labelID;
    int pinID;
    float rangeMin;
    float rangeMax;
    float calibrationOffset;
    float value = 0.0f;

public:
    Sensor(int label, int pin, float min, float max, float offset = 0.0f)
        : labelID(label), pinID(pin), rangeMin(min), rangeMax(max), calibrationOffset(offset), value(0.0f) {}

    virtual ~Sensor() {}

    float getMin() const { return rangeMin; }

    virtual float readData() {
        int rawValue = analogRead(pinID); 
        return rawValue; 
    };

    virtual float getValue() const { return value; }

    void setCalibrationOffset(float newOffset) { calibrationOffset = newOffset; }

    virtual void updateValue() {
        value = readData(); // Update the sensor value by reading new data
    }; 

    virtual void calibrate();
};

#endif
