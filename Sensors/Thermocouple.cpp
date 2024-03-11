#include "Thermocouple.h"

//Constructor used by rocketdriver
Thermocouple::Thermocouple(int labelID, int pinID, float linCoM, float linCoB,
                     ThermocoupleType type, float min, float max)
            : Sensor(labelID, pinID, linCoM, linCoB), 
                     thermocoupleType(type), rangeMin(min), rangeMax(max){}

//Constructor used if thermocouple tolerance is ignored
Thermocouple::Thermocouple(int labelID, int pinID, float linCoM, float linCoB)
            :Sensor(labelID, pinID, linCoM, linCoB),
            thermocoupleType(DEFAULT_THERMOCOUPLE_TYPE){setMyRange();}

//Constructor used for uncalibrated sensors
Thermocouple::Thermocouple(int labelID, int pinID)
            :Sensor(labelID, pinID, 1.0f, 0.0f),
            thermocoupleType(DEFAULT_THERMOCOUPLE_TYPE){setMyRange();}

//Getters for the range of values tolerated by the thermocouple
ThermocoupleType Thermocouple::getType() const {return thermocoupleType;}
float Thermocouple::getRangeMin() const {return rangeMin;}
float Thermocouple::getRangeMax() const {return rangeMax;}

//Sets the sensor's tolerable range based on the thermocouple's type
void Thermocouple::setMyRange(){setRange(thermocoupleType);}


// ***** TODO: Fill out the values in the setRange method *****

//Sets the sensor's tolerable range based on the given thermocouple's type
void Thermocouple::setRange(ThermocoupleType currentType)
{
    switch (currentType)
    {
    case ThermocoupleType.K:
        rangeMin = 0.0f;
        rangeMax = 0.0f;
        break;
    case ThermocoupleType.T
        rangeMin = 0.0f;
        rangeMax = 0.0f;
        break;
    default:
        rangeMin = 0.0f;
        rangeMax = 0.0f;
        break;
    }
}