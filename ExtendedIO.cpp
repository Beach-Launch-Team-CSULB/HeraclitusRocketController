#include <map>
#include "ExtendedIO.h"
#include "iostream"
#include "Config.h"

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

// Mapping from pin to {bit offset, port}
// Port A = 0 ... D = 3
std::map<int, std::array<int, 2>> pinMap = {
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

std::map<std::string, uint32_t> baseRegs = {
    {"PCR", 0x40049000},
    {"PCOR", 0x400FF048},
    {"PSOR", 0x400FF044},
    {"PDDR", 0x400FF014}
}

*PTC_DATA_DIRECTION |= 1;
*PTD_DATA_DIRECCTION |= 1;
 

void ExtendedIO::pinModeExtended(int pin, int isGPIO) {
    //Initilzes pin and sets mode to GPIO, this is only working for PORTx_PCRn registers 
    
    //Gets the exact address of the pin # passed in
    volatile uint32_t* registerAddress = static_cast<volatile uint32_t*>(pin_address_map[pin]);  

    
    *registerAddress |= (isGPIO << 8); // Sets it to GPIO Mode, 0 is INPUT, 1 is OUTPUT
    


    //If you need another mode add it here and add an argument, as of now idk what else is needed
}

void ExtendedIO::digitalWriteExtended(int pin, int value) {
    //Pin digital is getting sent here 

    volatile uint32_t* registerAddress = static_cast<volatile uint32_t*>(pin_address_map[pin]);
    volatile uint32_t* theonlyoneonPTD = static_cast<volatile uint32_t*>(PTD10_PCR);

    if(value==1){
          //Duck-Tape Code I know this is bad :<   -Bonnie
        if(*registerAddress == *theonlyoneonPTD){  //if PTD       //FOR BRANDON: Should be executing here with pin = 87 and value = 1
            //volatile uint32_t* registerPSORAddress = static_cast<volatile uint32_t*>(PTD_ADDRESS_SET);  
            //*registerPSORAddress |= (value << pin_PSOR_map[pin]); //Write 1 to the offset spot

            volatile uint32_t* registerPDORAddress = static_cast<volatile uint32_t*>(PTD_ADDRESS_DATA); 
            *registerPDORAddress |= (value << pin_offset_map[pin]); //Write 1 to "Drive" bit
        }
        else{  // PTC
            //volatile uint32_t* registerPSORAddress = static_cast<volatile uint32_t*>(PTC_ADDRESS_SET); 
            //*registerPSORAddress |= (value << pin_PSOR_map[pin]); //Write 1 to the offset spot

            volatile uint32_t* registerPDORAddress = static_cast<volatile uint32_t*>(PTC_ADDRESS_DATA); 
            *registerPDORAddress |= (value << pin_offset_map[pin]); //Write 1 to "Drive" bit
        }
    }else{
          if(*registerAddress == *theonlyoneonPTD){  //if PTD
            //volatile uint32_t* registerPSORAddress = static_cast<volatile uint32_t*>(PTD_ADDRESS_CLEAR); 
            //*registerPSORAddress |= (value << pin_PSOR_map[pin]); //Write 0 to the offset spot
            volatile uint32_t* registerPDORAddress = static_cast<volatile uint32_t*>(PTD_ADDRESS_DATA); 
            *registerPDORAddress |= (value << pin_offset_map[pin]); //Write 0 to "Drive" bit
        }
        else{  // PTC
            //volatile uint32_t* registerPSORAddress = static_cast<volatile uint32_t*>(PTC_ADDRESS_CLEAR); 
            //*registerPSORAddress |= (value << pin_PSOR_map[pin]); //Write 0 to the offset spot
            volatile uint32_t* registerPDORAddress = static_cast<volatile uint32_t*>(PTD_ADDRESS_DATA); 
            *registerPDORAddress |= (value << pin_offset_map[pin]); //Write 0 to "Drive" bit
        }
    }
}

int ExtendedIO::digitalPinToBit(int pin) {
    pinMap[pin][0] = offset;
    if (offset == pinMap.end()) return -1;
    return offset;
}

int ExtendedIO::digitalPinToPort(int pin) {
    pinMap[pin][1] = port;
    if (port == pinMap.end()) return -1;
    return port;
}

uint32_t ExtendedIO::fetchRegister(int pin, Register_Name reg) {
    register = baseRegs[reg];
    if (register = baseRegs.end()) return -1
    if (register == "PCR") {
        return volatile uint32_t (register + digitalPinToPort(pin) * 0x1000 + digitalPinToBit(pin) * 4);
    }
    else {
        return volatile uint32_t (register + 0x40 * digitalPinToPort(pin));
    }
}