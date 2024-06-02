#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <ADC.h>

class Sensor {
private:
    const int labelID;
    const int pinID;

    float linCoefM;
    float linCoefB;

    float value;

public:
    //Optional Constructor for an uncalibrated sensor
    Sensor():
        labelID(0), pinID(0), linCoefM(1.0f), linCoefB(0.0f), value(0.0f) {};
    Sensor(int label, int pin);
    
    //Primary Constructor for sensors
    Sensor(int label, int pin, float linCoM, float linCoB);

    float readDataRaw(ADC &adc);             // returns the analog voltage read from the pin
    virtual void updateValue(ADC &adc);      // makes this sensor do its job
    virtual float getCurrentValue(ADC &adc); // updates the value and returns it
    float getLastValue() const;      // gets the value

    //calibration methods from the gui should have a warning/confirmation message
    void resetCalibration();     // sets linear coeffecients to 1 and 0
    void setCalibrationParametersM(float linCoefM); // sets linear coeffecients
    void setCalibrationParametersB(float linCoefB);
    float getCalibrationSlope(); 
    float getCalibrationIntercept();

    bool hasID(int id);
    //  Aurum's Notes:
    // Pressure Transducer and Load Cell: To calibrate, we need to take pressure/force readings
    //  from a list of known pressure/weight values and create a line of best fit.
    // Thermocouple: Calibrate by reading the value at a known temperature like boiling or
    //  or freezing water, then add/subtract the calibration factor.
    //  Linear algebra should work for the calibration of each of our sensors.
    //  Future sensor integration should be able to ovverride any methods anyway
};

#endif
