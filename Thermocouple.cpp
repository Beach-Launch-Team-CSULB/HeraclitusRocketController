#ifndef THERMOCOUPLE_H
#define THERMOCOUPLE_H

// Reference Dan's THERMOCOUPLE in TemperatureSensorClass.h

#include "Sensor.h" // Ensure this path is correct based on your project structure
#include <string>

// Enum for different types of thermocouples
enum class ThermocoupleType {
    K, // Type K (Nickel-Chromium / Nickel-Alumel)
    T // Type T (Copper / Constantan)
};

class Thermocouple : public Sensor {
private:
    ThermocoupleType type;

public:
    // Constructor
    Thermocouple(int labelID, int pinID, std::string unit, float rangeMin, float rangeMax,
                 ThermocoupleType type, float calibrationOffset = 0.0f)
    : Sensor(labelID, pinID, unit, rangeMin, rangeMax, calibrationOffset), type(type) {}

    // Getter for the thermocouple type
    ThermocoupleType getType() const {
        return type;
    }
};

#endif // THERMOCOUPLE_H
