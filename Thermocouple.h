#ifndef THERMOCOUPLE_H
#define THERMOCOUPLE_H

#include "Sensor.hpp"
#include <string>

// Different types of thermocouples to support different temperature ranges and characteristics.
enum class ThermocoupleType {
    K, // Type K (Nickel-Chromium / Nickel-Alumel)
    T // Type T (Copper / Constantan)
};


class Thermocouple : public Sensor {
    private:
        ThermocoupleType thermocoupleType;

    public:
        // Constructor
        Thermocouple(int labelID, int pinID, float rangeMin, float rangeMax,
                    ThermocoupleType type, float calibrationOffset = 0.0f)
            : Sensor(labelID, pinID, rangeMin, rangeMax, calibrationOffset), thermocoupleType(type) {
        }

        ThermocoupleType getType() const {
            return thermocoupleType;
        }

};

#endif
