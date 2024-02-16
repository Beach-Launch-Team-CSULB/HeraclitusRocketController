#include "PressureTransducer.h" // Include the header file for the PressureTransducer class

// Constructor implementation if needed, though initialization is handled by the Sensor base class
PressureTransducer::PressureTransducer(int label, int pin, const std::string& unit, 
                                       float min, float max, float offset)
    : Sensor(label, pin, unit, min, max, offset) {
    // Any additional initialization specific to PressureTransducer can go here
}

// Destructor - Implement if needed for cleanup
PressureTransducer::~PressureTransducer() {
    // Cleanup resources if necessary
}

// Implement the readData() method to read from the pressure transducer
float PressureTransducer::readData() {
    int rawValue = analogRead(pinID); // Read the raw value from the sensor pin
    float voltage = (rawValue * 5.0) / 1023.0; // Convert raw value to voltage
    // Placeholder conversion logic, replace with actual conversion based on your sensor
    float pressure = (voltage - calibrationOffset) * (rangeMax - rangeMin) / 5.0 + rangeMin;
    return pressure; // Return the calculated pressure value
}

// Implement the updateValue() method to update the sensor's current value
void PressureTransducer::updateValue() {
    value = readData(); // Update the sensor value by reading new data
    // Additional logic to handle new value can be added here
}


