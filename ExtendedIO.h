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
        int digitalPinToBit(int pin);
        int digitalPinToPort(int pin);
        enum Register_Name {
            PCR,
            PCOR,
            PSOR,
            PDDR
        };
};

#endif
