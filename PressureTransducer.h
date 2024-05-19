#ifndef PRESSURE_TRANSDUCER_H
#define PRESSURE_TRANSDUCER_H


#include "Sensor.h" // Ensure this includes the path to the Sensor base class
#include <Arduino.h> // For hardware interfacing functions

enum E_PressureUnit {psi, atm};

#define DEFAULT_PRESSURE_UNIT psi


class PressureTransducer : public Sensor {
    private:
    E_PressureUnit outputUnit;

    public:
        //Constructor used by rocketdriver
        PressureTransducer(int labelID, int pinID, float linCoM, float linCoB);

        //Constructor used for uncalibrated sensors
        PressureTransducer(int labelID, int pinID);



        E_PressureUnit getUnitEnum();
        void changeOutputUnit(E_PressureUnit newUnitSystem);
};

#endif // PRESSURE_TRANSDUCER_H
