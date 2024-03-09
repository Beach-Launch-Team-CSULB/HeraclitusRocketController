#include "Thermocouple.h"

//Constructor
Thermocouple::Thermocouple(int labelID, int pinID, float linCoM, float linCoB,
                     ThermocoupleType type, float min, float max)
            : Sensor(labelID, pinID, linCoM, linCoB), 
                     thermocoupleType(type), rangeMin(min), rangeMax(max){
}

ThermocoupleType Thermocouple::getType() const {return thermocoupleType;}

float Thermocouple::getRangeMin() const {return rangeMin;}
float Thermocouple::getRangeMax() const {return rangeMax;}


//float Thermocouple::readData() override {}