#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>


class Sensor {
private:
    const int labelID;
    const int pinID;

    // float rangeMin;
    // float rangeMax;
    // float calibrationOffset;

    float linCoefM;
    float linCoefB;

    float value;

public:
    //Optional Constructor for an uncalibrated sensor
    Sesnor(in label, int pin);
    
    Sensor(int label, int pin, float linCoM, float linCoB);
        //: labelID(label), pinID(pin), linCoefM(linCoM), linCoefB(linCoB), value(0.0f) {}
        //  Note: implimentation should not occur in header files 


    // virtual ~Sensor();
    // Aurum's Note: I don't know if overriding destructors with empty implimentations will
    //   cause problems with C++'s automatic garbage collection. I also dont know if it won't
    //   either, so... I'm gonna just comment all of these out for now just to be safe.
    //   Although, tbh we the rocket driver shouldn't be calling these at any point in operations
    //   anyway so idk why we would need to handle this

    // float getMin() const;
    // float getMax() const;

    float readDataRaw();             // returns the analog voltage read from the pin
    virtual void updateValue();      // makes this sensor do its job
    virtual float getCurrentValue(); // updates the value and returns it
    float getValue() const;          // gets the value

    //calibration methods from the gui should have a warning/confirmation message
    void enterCalibrationMode();     // sets linear coeffecients to 1 and 0
    void setCalibrationParameters(float linCoefM, float linCoefB); // sets linear coeffecients

    // outdated idea. Implimenting
    // void setCalibrationOffset(float newOffset);

    //  Aurum's Notes:
    // Pressure Transducer and Load Cell: To calibrate, we need to take pressure/force readings
    //  from a list of known pressure/weight values and create a line of best fit.
    // Thermocouple: Calibrate by reading the value at a known temperature like boiling or
    //  or freezing water, then add/subtract the calibration factor.
    //  Linear algebra should work for the calibration of each of our sensors.
    //  Future sensor integration should be able to ovverride any methods anyway
};

#endif
