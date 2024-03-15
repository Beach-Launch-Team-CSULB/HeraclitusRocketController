#include "LoadCell.h" // Include the header file for the LoadCell class


// 3/12/2024 Depreciated: See Trauma Response



//Constructor used by rocketdriver
LoadCell::LoadCell(int labelID, int pinID, float linCoM, float linCoB)
    : Sensor(labelID, pinID, linCoM, linCoB){}

//Constructor used for uncalibrated sensors
LoadCell::LoadCell(int labelID, int pinID)
    : Sensor(labelID, pinID){}
