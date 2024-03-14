#include "ExtendedIO.h"
#include "iostream"
#include "Config.h"

void ExtendedIO::pinModeExtended() {
    //Placeholder 
    
}

void ExtendedIO::digitalWriteExtended() {

    //Example placeholder

    volatile uint32_t *portc_pcr16 = (volatile uint32_t *)(400 + 0x40); // Example, replace PORTC_BASE + 0x40 with actual address
    *portc_pcr16 = (1<<24) | // Clear ISF
                (2<<16) | // IRQC: Falling-edge interrupts
                (1<<1)  | // PE: Enable pull resistor
                (1<<0);   // PS: Select pull-up resistor
    *portc_pcr16 |= (1<<8);  // MUX: GPIO functionality (Check correct value for GPIO)

}