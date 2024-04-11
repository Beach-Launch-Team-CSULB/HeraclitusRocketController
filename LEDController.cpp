#include "LEDController.h"

void LEDController::init()
{
    ledArray.resetDevices();
    ledArray.init();

    setLED(0, GRAY);
    setLED(1, GRAY);
}

void LEDController::setLED(int ledID, Color newColor)
{
    if(ledID == 0)
    {
        ledArray.setChannelPWM(0, newColor.r);
        ledArray.setChannelPWM(1, newColor.g);
        ledArray.setChannelPWM(2, newColor.b);
    }
    else
    {
        ledArray.setChannelPWM(3, newColor.r);
        ledArray.setChannelPWM(4, newColor.g);
        ledArray.setChannelPWM(5, newColor.b);
    }
}