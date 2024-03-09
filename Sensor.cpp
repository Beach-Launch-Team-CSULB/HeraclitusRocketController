#include "Sensor.h"

//Aurum's Note: I wanted Sensor to be an abstract class, but based on my research the PT, TC, and
//  LC class should all be able to function properly with the same basic methods. I'm going to
//  keep them as child classes incase anything does come up, however for now the children are going
//  to be mostly empty implimentations of the Sensor base class.

//  For context, all of the sensor nodes just need to be calibrated to read their input and run 
//  some linear algebra for their output value.

Sensor::Sensor(int label, int pin, float linCoM, float linCoB)
    : labelID(label), pinID(pin), linCoefM(linCoM), linCoefB(linCoB), value(0.0f) {}

Sensor::Sensor(int label, int pin)
    : labelID(label), pinID(pin), linCoefM(1f), linCoefB(0f), value(0f) {}

float Sensor::getValue() const { return value; }

float Sensor::readDataRaw() {
    int rawValue = analogRead(pinID); 
    return rawValue; 
};


//void Sensor::setCalibrationOffset(float newOffset) { calibrationOffset = newOffset; }

void Sensor::updateValue() {
    value = linCoefM*readDataRaw()+linCoefB; // Update the sensor value by reading new data
}

float Sensor::getCurrentValue() {
    updateValue();
    return value;
}

void Sensor::enterCalibrationMode()
{ 
    linCoefM = 1f;
    linCoefB = 0f;
}

void Sensor::setCalibrationParameters(float linCoM, float linCoB)
{
    linCoefM = linCoM;
    linCoefB = linCoB;
}
