#ifndef THERMOCOUPLE_H
#define THERMOCOUPLE_H

#include "Sensor.h"
//#include <string>

// Different types of thermocouples to support different temperature ranges and characteristics.
enum class ThermocoupleType {
    K, // Type K (Nickel-Chromium / Nickel-Alumel)
    T // Type T (Copper / Constantan)
};


class Thermocouple : public Sensor {
    private:
        ThermocoupleType thermocoupleType;
        float rangeMin;
        float rangeMax;

    public:
        // Constructor
        Thermocouple(int labelID, int pinID, float linCoM, float linCoB, //Sensor fields
                     ThermocoupleType type, float min, float max); //Thermocouple fields

        ThermocoupleType getType() const;
        float getRangeMin() const;
        float getRangeMax() const;


};

#endif
