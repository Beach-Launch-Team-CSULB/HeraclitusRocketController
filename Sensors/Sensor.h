#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

//TODO: move ID definitions to config.h after branch is merged with main

//Each int is 32 bits, meaning we can have 32 unique sensor bitmasks
#define PT_LOX_HIGH_ID (1<<0)      //00000000 00000001
#define PT_FUEL_HIGH_ID (1<<1)     //00000000 00000010
#define PT_LOX_DOME_ID (1<<2)      //00000000 00000100
#define PT_FUEL_DOME_ID (1<<3)     //00000000 00001000
#define PT_LOX_TANK_1_ID (1<<4)    //00000000 00010000
#define PT_LOX_TANK_2_ID (1<<5)    //00000000 00100000
#define PT_FUEL_TANK_1_ID (1<<6)   //00000000 01000000
#define PT_FUEL_TANK_1_ID (1<<7)   //00000000 10000000
#define PT_PNUEMATICS (1<<8)       //00000001 00000000
#define PT_LOX_INLET_ID (1<<9)     //00000010 00000000
#define PT_FUEL_INLET_ID (1<<10)   //00000100 00000000
#define PT_FUEL_INJECTOR_ID (1<<11)//00001000 00000000
#define PT_CHAMBER_1_ID (1<<12)    //00010000 00000000
#define PT_CHAMBER_2_ID (1<<13)    //00100000 00000000

#define TC_1 (1<<16)
#define TC_2 (1<<17)
#define TC_3 (1<<18)
#define TC_4 (1<<19)
//We might need up to 12 thermocouples placed in groups of 3

#define LC_1 (1<<28)
#define LC_2 (1<<29)
#define LC_3 (1<<30)
#define LC_4 (1<<31)

class Sensor {
private:
    const int labelID;
    const int pinID;

    float linCoefM;
    float linCoefB;

    float value;

public:
    //Optional Constructor for an uncalibrated sensor
    Sesnor(int label, int pin);
    
    //Primary Constructor for sensors
    Sensor(int label, int pin, float linCoM, float linCoB);

    float readDataRaw();             // returns the analog voltage read from the pin
    virtual void updateValue();      // makes this sensor do its job
    virtual float getCurrentValue(); // updates the value and returns it
    float getLastValue() const;          // gets the value

    //calibration methods from the gui should have a warning/confirmation message
    void resetCalibration();     // sets linear coeffecients to 1 and 0
    void setCalibrationParameters(float linCoefM, float linCoefB); // sets linear coeffecients
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
