#include "LoadCell.h" // Include the header file for the LoadCell class


// Using Sensor's constructor initialization list
LoadCell::LoadCell(int labelID, int pinID, float linCoM, float linCoB)
    : Sensor(labelID, pinID, linCoM, linCoB){
}

//float LoadCell::readData() override {}