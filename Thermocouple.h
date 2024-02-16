#ifndef THERMOCOUPLE_H
#define THERMOCOUPLE_H

#include "Sensor.h"
#include <string>

// Define an enumeration for different types of thermocouples to support different temperature ranges and characteristics.
enum class ThermocoupleType {
    K, // Type K (Nickel-Chromium / Nickel-Alumel)
    T // Type T (Copper / Constantan)
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
    }

    ThermocoupleType getType() const {
        return thermocoupleType;
    }

};

#endif // THERMOCOUPLE_H
