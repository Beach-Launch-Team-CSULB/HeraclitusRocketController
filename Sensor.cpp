#include "Sensor.h"

//Constructor used by rocketdriver
Sensor::Sensor(int label, int pin, float linCoM, float linCoB)
    : labelID(label), pinID(pin), linCoefM(linCoM), linCoefB(linCoB) 
    {
        value = 0.0f;
    }

/*Constructor for uncalibrated sensors
Sensor::Sensor(int label, int pin)
    : labelID(label), pinID(pin), linCoefM(1.0f), linCoefB(0.0f), value(0.0f) {}
*/

//Returns the last value taken by the sensor
float Sensor::getLastValue() const { return value; }

//Gets an integer between 0-1023 coresponding to the sensor's current analog volatage
float Sensor::readDataRaw(ADC &adc)
{
    int rawValue = adc.analogRead(this->pinID); 
    return rawValue; 
};

//Rads the sensor's analog input, calibrates the data, and sets the sensor's value
void Sensor::updateValue(ADC &adc)
{
    this->value = linCoefM * readDataRaw(adc) + linCoefB; // Update the sensor value by reading new data
}

//Updated the sensor's value and returns the new value
float Sensor::getCurrentValue(ADC &adc)
{
    updateValue(adc);
    return this->value;
}


//Sets the linear coefficients to their default values for calibrating
void Sensor::resetCalibration()
{ 
    linCoefM = 1.0f;
    linCoefB = 0.0f;
}

//Sets the linear coefficients to new calibration values
void Sensor::setCalibrationParametersM(float linCoefM)
{
    linCoefM = linCoefM;
}

void Sensor::setCalibrationParametersB(float linCoefB)
{
    linCoefB = linCoefB;
}

//Getters for the linear coefficients
float Sensor::getCalibrationSlope() {return this->linCoefM;}
float Sensor::getCalibrationIntercept() {return this->linCoefB;}

//Optional function demonstrating how bitmasks can be used
bool Sensor::hasID(int id)
{
    return id & labelID;
}
