#include <map>
#include "ExtendedIO.h"
#include "iostream"
#include "Config.h"

 
void ExtendedIO::pinModeExtended(int pin, int isGPIO, int dataDirection) {
    /*  Argument 1: Pin # designation specified on the ALARA V2.x MCU Pin Map and gets the address 
        Argument 2: Specifies if this is a General Purpose Input/Output pin or not 
        Manually writes to Registers that define given pin behaviors
    */
    //TODO: Add for off 
    volatile uint32_t* PCR = digitalPinToPort(pin,PCR);     // Gets the exact address of the pin control register
    *PCR |= (isGPIO << 8);                                  // Sets pin PCR to GPIO Mode, 0 is INPUT, 1 is OUTPUT

    volatile uint32_t* PDDR = digitalPinToPort(pin, PDDR);  // Gets the exact address of the Port Data Direction Register
    int PDDR_Offset = digitalPinToBit(pin)                  // Gets bit offset for PDDR Register 
    *PDDR |= (dataDirection << PDDR_Offset);                // Sets pin PDDR to dataDirection Value at correct bit offset
}

void ExtendedIO::digitalWriteExtended(int pin, int value) {
    /*  Argument 1: Pin # designation specified on the ALARA V2.x MCU Pin Map and gets the address 
        Argument 2: 1 High, 0 Low
        Manually Writes Commands to Ports, Pinmode must be set prior
    */
    int pinBitOffset = digitalPinToBit(pin);                    // Gets bit offset for both PCOR & PSOR Register 
    if (value == 0){  // Clear port to 0: Low
        volatile uint32_t* PCOR = digitalPinToPort(pin,PCOR);   // Gets the exact address of the Port Clear Output Register
        *PCOR |= (0 << pinBitOffset);                           // Sets pin PCOR to 0 (Low) at correct bit offset
    }
    if (value == 1){  // Sets port to 1: High
        volatile uint32_t* PSOR = digitalPinToPort(pin,PSOR);   // Gets the exact address of the Port Set Output Register
        *PSOR |= (1 << pinBitOffset);                           // Sets pin PSOR to 1 (High) at correct bit offset
    }
    
}

int ExtendedIO::digitalPinToBit(int pin) {
    pinMap[pin][0] = offset
    if (offset == pinMap.end()) return -1;
    return offset
}

int ExtendedIO::digitalPinToPort(int pin) {
    pinMap[pin][1] = port
    if (port == pinMap.end()) return -1;
    return port
}

