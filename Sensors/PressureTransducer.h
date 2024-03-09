#ifndef PRESSURE_TRANSDUCER_H
#define PRESSURE_TRANSDUCER_H

#include "Sensor.h" // Ensure this includes the path to the Sensor base class
#include <Arduino.h> // For hardware interfacing functions

enum E_PressureUnit {psi, atm};

class PressureTransducer : public Sensor {
    private:
    E_PressureUnit outputUnit;

    public:
        // Using Sensor's constructor initialization list
        PressureTransducer(int labelID, int pinID, float linCoM, float linCoB);
            //: Sensor(labelID, pinID, linCoM, linCoB){}

        //~PressureTransducer();

        E_PressureUnit getUnitEnum();
        void changeOutputUnit(E_PressureUnit newUnitSystem);
};

#endif // PRESSURE_TRANSDUCER_H
