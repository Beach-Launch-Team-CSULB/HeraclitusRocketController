#ifndef EXTENDEDIO_H
#define EXTENDEDIO_H
#include <map>

class ExtendedIO { 
    public:
        static std::map<int, void*> pin_address_map; 
    
        static void pinModeExtended(int pin, int value);
        static void digitalWriteExtended(int pin, int value);
};

#endif
