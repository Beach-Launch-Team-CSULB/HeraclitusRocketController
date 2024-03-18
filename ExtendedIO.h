#ifndef EXTENDEDIO_H
#define EXTENDEDIO_H
#include <cstdint>

enum RegisterName {
    PCR,    // 4004_9000 
    PCOR,   // 400FF048
    PSOR,   // 400FF044
    PDDR    // 400FF014
};

class ExtendedIO { 
    public: 
        static void pinModeExtended(int pin, int value, int data_direction);
        static void digitalWriteExtended(int pin, int value);
    private:
        static int digitalPinToBit_int(int pin);
        static int digitalPinToPort_int(int pin);
        static volatile uint32_t fetchRegister(int pin, RegisterName reg);
};

#endif
