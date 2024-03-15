#ifndef THERMOCOUPLE_H
#define THERMOCOUPLE_H
/*/ 3/12/2024 Depreciated: See Trauma Response


#include "Sensor.h"
//#include <string>

// Different types of thermocouples to support different temperature ranges and characteristics.
enum class ThermocoupleType {
    K, // Type K (Nickel-Chromium / Nickel-Alumel)
    T // Type T (Copper / Constantan)
};

#define DEFAULT_THERMOCOUPLE_TYPE ThermocoupleType.K
//TODO: determine a default thermocouple type


class Thermocouple : public Sensor {
    private:
        ThermocoupleType thermocoupleType;
        float rangeMin;
        float rangeMax;

    public:
        // Constructor used by rocketdriver
        Thermocouple(int labelID, int pinID, float linCoM, float linCoB, //Sensor fields
                     ThermocoupleType type, float min, float max); //Thermocouple fields
                     //TODO: set min and max automatically from thermocouple type???

        //Constructor used if thermocouple fields are ignored
        Thermocouple(int labelID, int pinID, float linCoM, float linCoB);

        //Constructor used for uncalibrated sensors
        Thermocouple(int labelID, int pinID);

        //Getters for thermocouple fields
        ThermocoupleType getType() const;
        float getRangeMin() const;
        float getRangeMax() const;

        //Sets the thermocouple's range from a given thermocoupleType
        void setRange(ThermocoupleType); //TODO: set min and max from thermocouple type
        //Sets the thermocouple's range from its thermocoupleType
        void setMyRange();

};

*/
#endif

