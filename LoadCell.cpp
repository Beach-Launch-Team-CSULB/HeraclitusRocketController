#include "LoadCell.h" // Include the header file for the LoadCell class

// Constructor implementation if needed, though initialization is handled by the Sensor base class
LoadCell::LoadCell(int label, int pin, const std::string& unit, 
                                       float min, float max, float offset)
    : Sensor(label, pin, unit, min, max, offset) {
    // Any additional initialization specific to LoadCell can go here
}

// Destructor - Implement if needed for cleanup
LoadCell::~LoadCell() {
}

void LoadCell::calibrate() {
    return;
}