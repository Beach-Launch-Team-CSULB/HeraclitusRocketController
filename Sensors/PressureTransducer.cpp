#include "PressureTransducer.h" 

//Constructor used by rocketdriver
PressureTransducer::PressureTransducer(int labelID, int pinID, float linCoM, float linCoB)
            : Sensor(labelID, pinID, linCoM, linCoB){
                outputUnit = DEFAULT_PRESSURE_UNIT;
}

//Constructor used for uncalibrated sensors
PressureTransducer::PressureTransducer(int labelID, int pinID)
            : Sensor(labelID, pinID){
                outputUnit = DEFAULT_PRESSURE_UNIT;
}

//Getter and Setter for outputUnit enum
E_PressureUnit PressureTransducer::getUnitEnum(){return outputUnit;}
void PressureTransducer::changeOutputUnit(E_PressureUnit newUnitSystem)
{ 
    //TODO: impliment more pressure units and conversion functions
}




/* All of this will be handled by the Sensor base class after we calibrate each PT.
   I'm keeping the function as a comment block in case calibration alone isn't enough and
   we need to reference the technical math for the pressure transducer.

float PressureTransducer::readData() override {
    int rawValue = analogRead(pinID); // Read the raw value from the sensor pin
    float voltage = (rawValue * 5.0) / 1023.0; // Convert raw value to voltage

    // Placeholder conversion logic

    float pressure = (voltage - calibrationOffset) * (rangeMax - rangeMin) / 5.0 + rangeMin;
    return pressure;
}
*/



