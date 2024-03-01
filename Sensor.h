#ifndef SENSOR_H
#define SENSOR_H


class Sensor {
protected:
    int labelID;
    int pinID;
    float rangeMin;
    float rangeMax;
    float calibrationOffset;
    float value = 0.0f; // Explicit initialization

public:
    Sensor(int label, int pin, float min, float max, float offset = 0.0f)
    : labelID(label), pinID(pin), rangeMin(min), rangeMax(max), calibrationOffset(offset), value(0.0f) {}

    virtual ~Sensor() {}

    virtual float readData() {
        int rawValue = analogRead(pinID); 
        return rawValue; 
    };

    // Accessors and potentially setters if mutable operations needed
    float getMin() const { return rangeMin; }
    // Additional accessors for labelID, pinID, etc.

    virtual void updateValue() {
        value = readData(); // Update the sensor value by reading new data
    }; 

    virtual float getValue() const { return value; }

    void setCalibrationOffset(float newOffset) { calibrationOffset = newOffset; }

    void calibrate();
};

#endif // SENSOR_H
