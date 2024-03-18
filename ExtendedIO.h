#ifndef EXTENDEDIO_H
#define EXTENDEDIO_H
// #include <map>

class ExtendedIO { 
    public:
        //static std::map<int, void*> pin_address_map; 
        //static std::map<int, int> pin_PSOR_map; 
    
        static void pinModeExtended(int pin, int value, int data_direction);
        static void digitalWriteExtended(int pin, int value);

    private:
        static int digitalPinToBit(int pin);
        static int digitalPinToPort(int pin);
        static volatile uint32_t fetchRegister(int pin, RegisterName reg);
        static enum Register_Name {
            PCR, // 4004_9000 
            PCOR, // 400FF048
            PSOR, // 400FF044
            PDDR // 400FF014
        };
};

#endif
