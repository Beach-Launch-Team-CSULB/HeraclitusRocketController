#include "LEDController.h"

void LEDController::init()
{
    ledArray.resetDevices();
    ledArray.init();

    setLed(0, GRAY);
    setLed(1, GRAY);
    //ledColor1 = GRAY;
    //ledColor2 = GRAY;
}

void LEDController::setLed(int ledID, Color newColor)
{
    if(ledID == 0)
    {
        ledArray.setChannelPWM(0, newColor.r);
        ledArray.setChannelPWM(1, newColor.g);
        ledArray.setChannelPWM(2, newColor.b);
        //ledColor1 = newColor;
    }
    else
    {
        ledArray.setChannelPWM(3, newColor.r);
        ledArray.setChannelPWM(4, newColor.g);
        ledArray.setChannelPWM(5, newColor.b);
        //ledColor2 = newColor;
    }
}
