#include <FlexCAN_T4.h>

class CANDriver {
    private:
        bool isFD
    public:
        CANDriver(bool)
        // returnVal write(uint8_t)
        // returnVal read(uint8_t)
        bool getIsFD()
}

// This software needs to have support for both CAN2.0 and CANFD. 
// The imported library has support for both