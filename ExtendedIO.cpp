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

// Mapping from pin to {bit offset, port}
// Port A = 0 ... D = 3
std::map<int, std::array<int, 2>> pinMap = {
        {50, {0, 0}},
        {51, {1, 0}},
        {52, {2, 0}},
        {53, {3, 0}},
        {54, {4, 0}},
        {55, {5, 0}},
        {58, {6, 0}},
        {59, {7, 0}},
        {60, {8, 0}},
        {61, {9, 0}},
        {62, {10, 0}},
        {63, {11, 0}},
        {64, {12, 0}},
        {65, {13, 0}},
        {66, {14, 0}},
        {67, {15, 0}},
        {68, {16, 0}},
        {69, {17, 0}},
        {72, {18, 0}},
        {73, {19, 0}},
        {75, {24, 0}},
        {76, {25, 0}},
        {77, {26, 0}},
        {78, {27, 0}},
        {79, {28, 0}},
        {80, {29, 0}},
        {81, {0, 1}},
        {82, {1, 1}},
        {83, {2, 1}},
        {84, {3, 1}},
        {85, {4, 1}},
        {86, {5, 1}},
        {87, {6, 1}},
        {88, {7, 1}},
        {89, {8, 1}},
        {90, {9, 1}},
        {91, {10, 1}},
        {92, {11, 1}},
        {95, {16, 1}},
        {96, {17, 1}},
        {97, {18, 1}},
        {98, {19, 1}},
        {99, {20, 1}},
        {100, {21, 1}},
        {101, {22, 1}},
        {102, {23, 1}},
        {103, {0, 2}},
        {104, {1, 2}},
        {105, {2, 2}},
        {106, {3, 2}},
        {109, {4, 2}},
        {110, {5, 2}},
        {111, {6, 2}},
        {112, {7, 2}},
        {113, {8, 2}},
        {114, {9, 2}},
        {115, {10, 2}},
        {116, {11, 2}},
        {117, {12, 2}},
        {118, {13, 2}},
        {119, {14, 2}},
        {120, {15, 2}},
        {123, {16, 2}},
        {124, {17, 2}},
        {125, {18, 2}},
        {126, {19, 2}},
        {127, {0, 3}},
        {128, {1, 3}},
        {129, {2, 3}},
        {130, {3, 3}},
        {131, {4, 3}},
        {132, {5, 3}},
        {133, {6, 3}},
        {136, {7, 3}},
        {137, {8, 3}},
        {138, {9, 3}},
        {139, {10, 3}},
        {140, {11, 3}},
        {141, {12, 3}},
        {142, {13, 3}},
        {143, {14, 3}},
        {144, {15, 3}}
    };

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
    pinMap[pin][0] = offset
    if (offset == pinMap.end()) return -1;
    return offset
}

int ExtendedIO::digitalPinToPort(int pin) {
    pinMap[pin][1] = port
    if (port == pinMap.end()) return -1;
    return port
}

int 