#ifndef EXTENDEDIO_H
#define EXTENDEDIO_H

class ExtendedIO { 
    public:
        static void pinModeExtended(int pin, int value);
        static void digitalWriteExtended(int pin, int value);
};

#endif
