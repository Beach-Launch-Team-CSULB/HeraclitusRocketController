#ifndef THERMOCOUPLE_H
#define THERMOCOUPLE_H

#include "Sensor.h"
#include <string>

// Define an enumeration for different types of thermocouples to support different temperature ranges and characteristics.
enum class ThermocoupleType {
    K, // Type K (Nickel-Chromium / Nickel-Alumel) - most common, wide temperature range
    T // Type T (Copper / Constantan) - better for lower temperatures, high accuracy
};

// Thermocouple class definition
class Thermocouple : public Sensor {
private:
    ThermocoupleType thermocoupleType; // Type of the thermocouple (K, J, T, etc.)

public:
    // Constructor
    Thermocouple(int labelID, int pinID, const std::string& unit, float rangeMin, float rangeMax,
                 ThermocoupleType type, float calibrationOffset = 0.0f)
        : Sensor(labelID, pinID, unit, rangeMin, rangeMax, calibrationOffset), thermocoupleType(type) {
        // Constructor implementation
    }

    // Override the Sensor's readData method to implement thermocouple-specific reading logic
    float readData() override {
        // Code to interface with hardware and read temperature data
        // Conversion from electrical signal to temperature based on thermocouple type
        return 0.0f; // Placeholder for actual reading logic
    }

    // Function to get the type of thermocouple
    ThermocoupleType getType() const {
        return thermocoupleType;
    }

    // Optionally, override other Sensor methods if thermocouple-specific behavior is needed
};

#endif // THERMOCOUPLE_H
