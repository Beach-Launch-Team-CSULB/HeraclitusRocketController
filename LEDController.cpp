#include "LEDController.h"
#include "Arduino.h"

LEDController::LEDController() {}

LEDController::LEDController(int pin1, int pin2, int pin3): pin1(pin1), pin2(pin2), pin3(pin3)
{
    pinMode(pin1, 1);
    digitalWrite(pin1, HIGH);
    pinMode(pin2, 1);
    digitalWrite(pin2, LOW);
    pinMode(pin3, 1);
    digitalWrite(pin3, LOW);
}

void LEDController::setLed(int val)
{
    if (val % 2) digitalWrite(this->pin1, LOW);
    else digitalWrite(this->pin1, HIGH);
    val /= 2;
    if (val % 2) digitalWrite(this->pin2, LOW);
    else digitalWrite(this->pin2, HIGH);
    val /= 2;
    if (val % 2) digitalWrite(this->pin3, LOW);
    else digitalWrite(this->pin3, HIGH);
}