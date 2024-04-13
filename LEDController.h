#include "PCA9685.h" // Standard PlatformIO file

//#define RED {1, 0, 0} //Testing
struct Color{int r, g, b;}; //Custom color structure where each value is an int 0-4096

#define BLACK Color{4096, 4096, 4096} //turns LED off
#define GRAY Color{3072, 3072, 3072} // Startup LED Color
#define WHITE Color{0, 0, 0} // Led1 for Standby

#define RED Color{0, 4096, 4096} // Led2 for Fire                           Used for Fire
#define ORANGE Color{0, 3584, 4096} // Led1 for Launch Sequence States      Led1 for Launch Sequence
#define YELLOW Color{256, 3072, 4096} // Led1 for Launch Sequence Arm       Abort
#define LIME Color{512, 128, 4096} //                                       Tank Press Arm
#define GREEN Color{4096, 256, 4096} // Led2 for Tank Press                 Tank Press
#define CYAN Color{4096, 256, 3072}
#define TEAL Color{4096, 3072, 2048} //                                     High Press Arm
#define BLUE Color{4096, 4096, 256} // Led2 for High Press                  High Press
#define PURPLE Color{3072, 4096, 2048} //Led2 for Vent
#define MAGENTA Color{1024, 4096, 1024} //                                  Vent
#define PINK Color{64, 3584, 256} //Led 2 for Abort

class LEDController
{
    private: 
    PCA9685 ledArray; // Library using default B000000 (A5-A0) i2c address, and default Wire @400kHz
    //Color ledColor1, ledColor2;

    public:
    //LEDController();
    void init(); //initializes ledArray
    void setLed(int ledID, Color newColor);
    //void setLedBlinking(int ledID, Color blinkColor, int blinkDuration); //blinkDuration in millis
    //void setLedBlinking(int ledID, Color blinkColor); //blinkDuration defaults to 1 second
};