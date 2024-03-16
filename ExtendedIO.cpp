#include <map>
#include "ExtendedIO.h"
#include "iostream"
#include "Config.h"

// Sets up PIN References so when a pin ID is passed in, you can find the exact register address to write to
static std::map<int, void*> pin_address_map = {
    {IGN1_ID,PTC16_PCR},
    {IGN2_ID,PTC14_PCR},
    {HP_ID,PTD10_PCR},
    {HV_ID,PTC19_PCR},
    {FMV_ID,PTC18_PCR},
    {LMV_ID,PTC17_PCR},
    {LV_ID,PTD10_PCR},
    {LDV_ID,PTC18_PCR},
    {LDR_ID,PTC17_PCR},
    {FV_ID,PTC16_PCR},
    {FDV_ID,PTC14_PCR},
    {FDR_ID,PTC13_PCR}
    };

// Sets up PIN References so when a pin ID is passed in, you can find the exact offset in the register 
static std::map<int, int> pin_PSOR_map = {
    {IGN1_ID,PTC16_OFFSET},
    {IGN2_ID,PTC14_OFFSET},
    {HP_ID,PTD10_OFFSET},
    {HV_ID,PTC19_OFFSET},
    {FMV_ID,PTC18_OFFSET},
    {LMV_ID,PTC17_OFFSET},
    {LV_ID,PTD10_OFFSET},
    {LDV_ID,PTC18_OFFSET},
    {LDR_ID,PTC17_OFFSET},
    {FV_ID,PTC16_OFFSET},
    {FDV_ID,PTC14_OFFSET},
    {FDR_ID,PTC13_OFFSET}
    };    
 
void ExtendedIO::pinModeExtended(int pin, int isGPIO) {
    //Initilzes pin and sets mode to GPIO, this is only working for PORTx_PCRn registers 
    
    //Gets the exact address of the pin # passed in
    volatile uint32_t* registerAddress = static_cast<volatile uint32_t*>(pin_address_map[pin]);  
    
    *registerAddress |= (isGPIO << 8); // Sets it to GPIO Mode, 0 is INPUT, 1 is OUTPUT
    


    //If you need anothe mode add it here and add an argument, as of now idk what else is needed
}

void ExtendedIO::digitalWriteExtended(int pin, int value) {
    volatile uint32_t* registerAddress = static_cast<volatile uint32_t*>(pin_address_map[pin]);
    volatile uint32_t* theonlyoneonPTD = static_cast<volatile uint32_t*>(PTD10_PCR);

    //Duck-Tape Code I know this is bad :<   -Bonnie
    if(*registerAddress == *theonlyoneonPTD){  //if PTD
        volatile uint32_t* registerPSORAddress = static_cast<volatile uint32_t*>(PTD_ADDRESS); 
        *registerPSORAddress |= (value << pin_PSOR_map[pin]); //Write value to the offset spot
    }
    else{  // PTC
        volatile uint32_t* registerPSORAddress = static_cast<volatile uint32_t*>(PTC_ADDRESS); 
        *registerPSORAddress |= (value << pin_PSOR_map[pin]); //Write value to the offset spot
    }
  

}