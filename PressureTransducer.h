#ifndef PRESSURE_TRANSDUCER_H
#define PRESSURE_TRANSDUCER_H

#include "Sensor.h" // Ensure this includes the path to the Sensor base class
#include <Arduino.h> // For hardware interfacing functions

class PressureTransducer : public Sensor {
    protected:
    uint32_t sampleRate; // Current sample rate
    // Additional variables for different sample rates if needed

public:
    // Using Sensor's constructor initialization list
    PressureTransducer(int label, int pin, const std::string& unit, 
                       float min, float max, float offset = 0.0f)
    : Sensor(label, pin, unit, min, max, offset) {}

    virtual ~PressureTransducer() {}

    // Implementing readData() to interface with the pressure transducer hardware
    float readData() override {
        // Example: Read analog voltage, convert to pressure
        int rawValue = analogRead(pinID); // Use analogRead from Arduino to read the sensor pin
        // Convert the raw value to a voltage assuming a 5V reference and a 10-bit ADC resolution
        float voltage = (rawValue * 5.0) / 1023.0;
        // Convert voltage to pressure. The conversion depends on the transducer's specifications
        // Placeholder conversion: assuming linear relation just for demonstration
        float pressure = (voltage - calibrationOffset) * (rangeMax - rangeMin) / 5.0 + rangeMin;
        return pressure;
    }

    // Implementing updateValue() to update the sensor's current value
    void updateValue() override {
        value = readData(); // Update the sensor value by reading new data
    }

    void setSampleRate(uint32_t rate) {
        sampleRate = rate;
    }
};

#endif // PRESSURE_TRANSDUCER_H
