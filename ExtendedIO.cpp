#include <map>
#include "ExtendedIO.h"
#include "iostream"
#include "Config.h"
#include <cstdint>
//#include <map>
#include <kinetis.h>
#include <SPI.h>


// Mapping from pin to {bit offset, port}
// Port A = 0 ... D = 3

//Static map used to associate digital pins to the bits and ports on the teensy
std::map<int, std::array<int,2>> pinMap = {
    {83, {16, 2}}, //used for IGN1_PIN_DIG and FV_PIN_DIG
    {81, {14, 2}}, //used for IGN2_PIN_DIG and FDV_PIN_DIG
    {87, {10, 3}}, //used for HP_PIN_DIG and LV_PIN_DIG
    {86, {19, 2}}, //used for HV_PIN_DIG
    {85, {18, 2}}, //used for FMV_PIN_DIG and LDV_PIN_DIG     if valves dont work, array might be {8,2}
    {84, {17, 2}}, //used for LMV_PIN_DIG and LDR_PIN_DIG
    {80, {13, 2}}  //used for FDR_PIN_DIG
};


// Base register addresses
// Used to calculate target register
std::map<RegisterName, uint32_t> baseRegs = {
    {PCR, 0x40049000},
    {PCOR, 0x400FF048},
    {PSOR, 0x400FF044},
    {PDDR, 0x400FF014},
    {PDOR, 0x400FF000}
};

// Finds the number of bits needed to shift from the port
int ExtendedIO::digitalPinToBit_int(int pin) {
    std::array<int,2> pinsArray = pinMap[pin];
    if (pinsArray.empty()) 
        return -1;
    return pinsArray[0];
}

// Finds the number of ports from the base register to this digital pin
int ExtendedIO::digitalPinToPort_int(int pin) {
    std::array<int,2> pinsArray = pinMap[pin];
    if (pinsArray.empty()) 
        return -1;
    return pinsArray[1];
}

// 
uint32_t ExtendedIO::fetchRegister(int pin, RegisterName reg) {
    // Gets and validates the register
    uint32_t registerAddress = baseRegs[reg];
    if (registerAddress == 0) 
        return 0;

    // Gets and validates the port
    int port = digitalPinToPort_int(pin);
    if (port == -1) 
        return 0;
    
    // Gets and validates the bits to shift
    int bitOffset = digitalPinToBit_int(pin);
    if (bitOffset == -1) 
        return 0;

    // 
    if (reg == PCR) {
        return uint32_t (registerAddress + port * 0x1000 + bitOffset * 4); }
    //
    else {
        return uint32_t (registerAddress + 0x40 * (port)); }
}

/*  Argument 1: Pin # designation specified on the ALARA V2.x MCU Pin Map and gets the address 
 *  Argument 2: Specifies if this is a General Purpose Input/Output pin or not 
 *  Manually writes to Registers that define given pin behaviors */
void ExtendedIO::pinModeExtended(int pin, int isGPIO, int dataDirection) {
    uint32_t PDDR_address = fetchRegister(pin, PDDR); // Gets the exact address of the Port Data Direction Register
    if(PDDR_address != 0){
        int PDDR_Offset = digitalPinToBit_int(pin); // Gets bit offset for PDDR Register 
        if(dataDirection == 1){
            (*(volatile uint32_t*)PDDR_address) |= (1 << PDDR_Offset); // Sets pin PDDR to 1 at correct bit offset 
        }
        else{
            (*(volatile uint32_t*)PDDR_address) &= !(1 << PDDR_Offset); // Sets pin PDDR to 0 at correct bit offset
        }
    }

    uint32_t PCR_address = fetchRegister(pin,PCR); // Gets the exact address of the pin control register
    if(PCR_address != uint32_t(0)){ // If it is a valid Pin with an address 
        if(isGPIO == 1){
            (*(volatile uint32_t*) PCR_address) = (1<<8); // Sets pin PCR to GPIO Mode, 0 is Analog/Disabled, 1 is GPIO
        }else{
            (*(volatile uint32_t*) PCR_address) = (0<<8); // Sets pin PCR to Analog/Disabled, 1 is GPIO
        }
    }
}

/*  Argument 1: Pin # designation specified on the ALARA V2.x MCU Pin Map and gets the address 
 *  Argument 2: 1 High, 0 Low
 *  Manually Writes Commands to Ports, Pinmode must be set prior */
void ExtendedIO::digitalWriteExtended(int pin, bool valveOpen) 
{
    int pinBitOffset = digitalPinToBit_int(pin); // Gets bit offset for both PCOR & PSOR Register
    uint32_t PDOR_address = fetchRegister(pin,PDOR); // Gets the exact address of the Port Clear Output Register
    if(PDOR_address != 0)
    {
        if(valveOpen)
            (*(volatile uint32_t*)PDOR_address) |= (1 << pinBitOffset); // Sets PDOR bit to 1 (High) at correct bit offset
        else
            (*(volatile uint32_t*)PDOR_address) &= !(1 << pinBitOffset); // Clears PDOR bit to 0 (Low) at correct bit offset
    }
}

/*
#include <map>
#include "ExtendedIO.h"
#include "iostream"
#include "Config.h"
#include <cstdint>
#include <map>
#include <kinetis.h>

// Mapping from pin to {bit offset, port}
// Port A = 0 ... D = 3
std::map<int, std::array<int,2>> pinMap = {
    {IGN1_PIN_DIG,{16, 2}},  
    {IGN2_PIN_DIG,{14,2}},
    {HP_PIN_DIG,{10,2}},
    {HV_PIN_DIG,{19,2}},
    {FMV_PIN_DIG,{18,2}},
    {LMV_PIN_DIG,{17,2}},
    {LV_PIN_DIG,{10,3}},
    {LDV_PIN_DIG,{8,2}},
    {LDR_PIN_DIG,{17,2}},
    {FV_PIN_DIG,{16,2}},
    {FDV_PIN_DIG,{14,2}},
    {FDR_PIN_DIG,{13,2}}
};

// Base register addresses
// Used to calculate target register
std::map<RegisterName, uint32_t> baseRegs = {
    {PCR, 0x40049000},
    {PCOR, 0x400FF048},
    {PSOR, 0x400FF044},
    {PDDR, 0x400FF014}
};


void ExtendedIO::extendedIOsetup() {
    SIM_SCGC5 |= SIM_SCGC5_PORTA;
    SIM_SCGC5 |= SIM_SCGC5_PORTB;
    SIM_SCGC5 |= SIM_SCGC5_PORTC;
    SIM_SCGC5 |= SIM_SCGC5_PORTD;
}

int ExtendedIO::digitalPinToBit_int(int pin) {
    auto it = pinMap.find(pin);
    if (it == pinMap.end()) return -1;
    return it->second[0];
}

int ExtendedIO::digitalPinToPort_int(int pin) {
    auto it = pinMap.find(pin);
    if (it == pinMap.end()) return -1;
    return it->second[1];
}

uint32_t ExtendedIO::fetchRegister(int pin, RegisterName reg) {
    auto regIt = baseRegs.find(reg);
    if (regIt == baseRegs.end()) return 0;

    int port = digitalPinToPort_int(pin);
    if (port == -1) return 0;

    int bitOffset = digitalPinToBit_int(pin);
    if (bitOffset == -1) return 0;

    uint32_t baseAddress = regIt->second;
    if (reg == PCR) {
        return uint32_t (baseAddress + port * 0x1000 + bitOffset * 4);
    } else {
        return uint32_t (baseAddress + 0x40 * port);
    }
}

void ExtendedIO::pinModeExtended(int pin, int isGPIO, int dataDirection) {
    /*  Argument 1: Pin # designation specified on the ALARA V2.x MCU Pin Map and gets the address 
        Argument 2: Specifies if this is a General Purpose Input/Output pin or not 
        Manually writes to Registers that define given pin behaviors
    
    
    uint32_t PCR_address = fetchRegister(pin,PCR);     // Gets the exact address of the pin control register
    if(PCR_address != uint32_t(0)){                             // If it is a valid Pin with an address 
        if(isGPIO == 1){
            (*(volatile uint32_t*) PCR_address) |= PORT_PCR_MUX(0x1);                          // Sets pin PCR to GPIO Mode, 0 is Analog/Disabled, 1 is GPIO
        }else{
            (*(volatile uint32_t*) PCR_address) &= PORT_PCR_MUX(0x0);                        // Sets pin PCR to Analog/Disabled, 1 is GPIO
        }
    }

    uint32_t PDDR_address = fetchRegister(pin, PDDR);  // Gets the exact address of the Port Data Direction Register
    if(PDDR_address != 0){
        int PDDR_Offset = digitalPinToBit_int(pin);          // Gets bit offset for PDDR Register 
        if(dataDirection == 1){
            (*(volatile uint32_t*)PDDR_address) |= (1 << PDDR_Offset);                 // Sets pin PDDR to 1 at correct bit offset 
        }
        else{
            (*(volatile uint32_t*)PDDR_address) &= (0 << PDDR_Offset);                 // Sets pin PDDR to 0 at correct bit offset
        }
    }
}

void ExtendedIO::digitalWriteExtended(int pin, int value) {
    /*  Argument 1: Pin # designation specified on the ALARA V2.x MCU Pin Map and gets the address 
        Argument 2: 1 High, 0 Low
        Manually Writes Commands to Ports, Pinmode must be set prior
    
    int pinBitOffset = digitalPinToBit_int(pin);                   // Gets bit offset for both PCOR & PSOR Register 
    if (value == 0){  // Clear port to 0: Low
        uint32_t PCOR_address = fetchRegister(pin,PCOR);     // Gets the exact address of the Port Clear Output Register
        if(PCOR_address != 0){                                        // If pin is correct & a register is returned 
            (*(volatile uint32_t*)PCOR_address) = (1 << pinBitOffset);                      // Clears PDOR bit to 0 (Low) at correct bit offset
        }
    }
    if (value == 1){  // Sets port to 1: High
        uint32_t PSOR_address = fetchRegister(pin,PSOR);     // Gets the exact address of the Port Set Output Register
        if(PSOR_address != 0){                                        // If pin is correct & a register is returned
            (*(volatile uint32_t*)PSOR_address) = (1 << pinBitOffset);                          // Sets PDOR bit to 1 (High) at correct bit offset
        }
    }
}

*/