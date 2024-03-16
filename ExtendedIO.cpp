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
static std::map<int, int> pin_PSOR_map = {
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
 
void ExtendedIO::pinModeExtended(int pin, int isGPIO) {
    //Initilzes pin and sets mode to GPIO, this is only working for PORTx_PCRn registers 
    
    //Gets the exact address of the pin # passed in
    volatile uint32_t* registerAddress = static_cast<volatile uint32_t*>(pin_address_map[pin]);  
    
    *registerAddress |= (isGPIO << 8); // Sets it to GPIO Mode, 0 is INPUT, 1 is OUTPUT
    


    //If you need anothe mode add it here and add an argument, as of now idk what else is needed
}

void ExtendedIO::digitalWriteExtended(int pin, int value) {
    //Pin digital is getting sent here 

    volatile uint32_t* registerAddress = static_cast<volatile uint32_t*>(pin_address_map[pin]);
    volatile uint32_t* theonlyoneonPTD = static_cast<volatile uint32_t*>(PTD10_PCR);

    if(value==1){
          //Duck-Tape Code I know this is bad :<   -Bonnie
        if(*registerAddress == *theonlyoneonPTD){  //if PTD
            volatile uint32_t* registerPSORAddress = static_cast<volatile uint32_t*>(PTD_ADDRESS_SET); 
            *registerPSORAddress |= (value << pin_PSOR_map[pin]); //Write value to the offset spot
        }
        else{  // PTC
            volatile uint32_t* registerPSORAddress = static_cast<volatile uint32_t*>(PTC_ADDRESS_SET); 
            *registerPSORAddress |= (value << pin_PSOR_map[pin]); //Write value to the offset spot
        }
    }else{
          if(*registerAddress == *theonlyoneonPTD){  //if PTD
            volatile uint32_t* registerPSORAddress = static_cast<volatile uint32_t*>(PTD_ADDRESS_CLEAR); 
            *registerPSORAddress |= (value << pin_PSOR_map[pin]); //Write value to the offset spot
        }
        else{  // PTC
            volatile uint32_t* registerPSORAddress = static_cast<volatile uint32_t*>(PTC_ADDRESS_CLEAR); 
            *registerPSORAddress |= (value << pin_PSOR_map[pin]); //Write value to the offset spot
        }
    }

  
  

}