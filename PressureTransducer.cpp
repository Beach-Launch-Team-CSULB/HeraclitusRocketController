#include "PressureTransducer.h" 

PressureTransducer::PressureTransducer(int label, int pin, const std::string& unit, 
                                       float min, float max, float offset)
    : Sensor(label, pin, unit, min, max, offset) {

}

// Destructor
PressureTransducer::~PressureTransducer() {
}

// Implement the readData() method to read from the pressure transducer
float PressureTransducer::readData() override {
    int rawValue = analogRead(pinID); // Read the raw value from the sensor pin
    float voltage = (rawValue * 5.0) / 1023.0; // Convert raw value to voltage

    // Placeholder conversion logic

    float pressure = (voltage - calibrationOffset) * (rangeMax - rangeMin) / 5.0 + rangeMin;
    return pressure;
}

void PressureTransducer::calibrate() override() {}


