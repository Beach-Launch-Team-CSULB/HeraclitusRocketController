#include "PCA9685.h" // Standard PlatformIO file
#include "Config.h"


class LEDController
{
    private: 
        PCA9685 ledArray; // Library using default B000000 (A5-A0) i2c address, and default Wire @400kHz
        //Color ledColor1, ledColor2;

    public:
        //LEDController();
        void init(); //initializes ledArray
        void setLED(int ledID, Color newColor);
        //void setLedBlinking(int ledID, Color blinkColor, int blinkDuration); //blinkDuration in millis
        //void setLedBlinking(int ledID, Color blinkColor); //blinkDuration defaults to 1 second
};