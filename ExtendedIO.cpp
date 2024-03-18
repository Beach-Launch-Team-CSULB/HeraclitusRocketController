#include <map>
#include "ExtendedIO.h"
#include "iostream"
#include "Config.h"

// Sets up PIN References so when a pin DIG ID is passed in, you can find the exact register address to write to
static std::map<int, void*> pin_address_map = {
    {IGN1_PIN_DIG,PTC16_PCR},
    {IGN2_PIN_DIG,PTC14_PCR},
    {HP_PIN_DIG,PTD10_PCR},
    {HV_PIN_DIG,PTC19_PCR},
    {FMV_PIN_DIG,PTC18_PCR},
    {LMV_PIN_DIG,PTC17_PCR},
    {LV_PIN_DIG,PTD10_PCR},
    {LDV_PIN_DIG,PTC18_PCR},
    {LDR_PIN_DIG,PTC17_PCR},
    {FV_PIN_DIG,PTC16_PCR},
    {FDV_PIN_DIG,PTC14_PCR},
    {FDR_PIN_DIG,PTC13_PCR}
    };

// Sets up PIN References so when a pin DIG ID is passed in, you can find the exact offset in the register 
static std::map<int, int> pin_offset_map = {
    {IGN1_PIN_DIG,PTC16_OFFSET},
    {IGN2_PIN_DIG,PTC14_OFFSET},
    {HP_PIN_DIG,PTD10_OFFSET},
    {HV_PIN_DIG,PTC19_OFFSET},
    {FMV_PIN_DIG,PTC18_OFFSET},
    {LMV_PIN_DIG,PTC17_OFFSET},
    {LV_PIN_DIG,PTD10_OFFSET},
    {LDV_PIN_DIG,PTC18_OFFSET},
    {LDR_PIN_DIG,PTC17_OFFSET},
    {FV_PIN_DIG,PTC16_OFFSET},
    {FDV_PIN_DIG,PTC14_OFFSET},
    {FDR_PIN_DIG,PTC13_OFFSET}
    };    

*PTC_DATA_DIRECTION |= 1;
*PTD_DATA_DIRECCTION |= 1;
 

 
void ExtendedIO::pinModeExtended(int pin, int isGPIO, int dataDirection) {
    /*  Argument 1: Pin # designation specified on the ALARA V2.x MCU Pin Map and gets the address 
        Argument 2: Specifies if this is a General Purpose Input/Output pin or not 
        Manually writes to Registers that define given pin behaviors
    */
    
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