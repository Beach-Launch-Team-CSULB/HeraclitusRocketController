#pragma once

class LEDController
{
    private:
        int pin1;
        int pin2;
        int pin3;

    public:
        LEDController();
        LEDController(int, int, int);
        void setLed(int);
};