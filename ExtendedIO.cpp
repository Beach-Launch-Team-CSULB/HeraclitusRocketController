#include <map>
#include "ExtendedIO.h"
#include "iostream"
#include "Config.h"

// Sets up PIN References so when a pin ID is passed in, you can find the exact register address to write to
static std::map<int, void*> pin_address_map = {
    {IGN1_ID,PTC16},
    {IGN2_ID,PTC14},
    {HP_ID,PTD10},
    {HV_ID,PTC19},
    {FMV_ID,PTC18},
    {LMV_ID,PTC17},
    {LV_ID, PTD10}
    
    };
 
void ExtendedIO::pinModeExtended(int pin, int isGPIO) {
    //Initilzes pin and sets mode to GPIO, this is only working for PORTx_PCRn registers 
    
    *pin_address_map[pin] |= (isGPIO<<8);  // Set MUX to GPIO functionality

    //If you need anothe mode add it here and add an argument, as of now idk what else is needed
    
}

void ExtendedIO::digitalWriteExtended(int pin, int value) {

    //Example placeholder

    volatile uint32_t *portc_pcr16 = (volatile uint32_t *)(400 + 0x40); // Example, replace PORTC_BASE + 0x40 with actual address
    *portc_pcr16 = (1<<24) | // Clear ISF
                (2<<16) | // IRQC: Falling-edge interrupts
                (1<<1)  | // PE: Enable pull resistor
                (1<<0);   // PS: Select pull-up resistor
  

}