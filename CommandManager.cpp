#include "CommandManager.h"
#include <iostream>


Rocket* CommandManager::rocket = nullptr;
CANDriver* CommandManager::comSystem = nullptr;

void CommandManager::init(Rocket* myRocket, CANDriver* myComSystem)
{
    rocket = myRocket;
    comSystem = myComSystem;
}

void CommandManager::checkCommand()
{
    uint32_t commandID = comSystem->readMessage();
    if(commandID == 255)
        return;
    Serial.println("Got a command!");
    Serial.println(commandID);
    switch(commandID)
    {
        case ABORT:
            rocket->abort();
            return;
        case VENT:
            rocket->vent();
            return;
        case FIRE:
            rocket->enterState(Fire);
            return;
        case IGNITE:
            rocket->enterState(Ignite);
            return;
        case TANK_PRESS:
            rocket->enterState(TankPress);
            return;
        case HIGH_PRESS:
            rocket->enterState(HighPress);
            return;
        case STANDBY:
            rocket->enterState(Standby);
            return;
        case TEST:
            rocket->enterState(Test);
            return;

        case LV_OPEN:
            rocket->setValve(LV_ID, true);
            return;
        case LDV_OPEN:
            rocket->setValve(LDV_ID, true);
            return;
        case HV_OPEN:
            rocket->setValve(HV_ID, true);
            return;
        case FV_OPEN:
            rocket->setValve(FV_ID, true);
            return;
        case FDV_OPEN:
            rocket->setValve(FDV_ID, true);
            return;
        case HP_OPEN:
            rocket->setValve(HP_ID, true);
            return;
        case LDR_OPEN:
            rocket->setValve(LDR_ID, true);
            return;
        case FDR_OPEN:
            rocket->setValve(FDR_ID, true);
            return;
        case LMV_OPEN:
            rocket->setValve(LMV_ID, true);
            return;
        case FMV_OPEN:
            rocket->setValve(FMV_ID, true);
            return;
        case LV_CLOSE:
            rocket->setValve(LV_ID, false);
            return;
        case LDV_CLOSE:
            rocket->setValve(LDV_ID, false);
            return;
        case HV_CLOSE:
            rocket->setValve(HV_ID, false);
            return;
        case FV_CLOSE:
            rocket->setValve(FV_ID, false);
            return;
        case FDV_CLOSE:
            rocket->setValve(FDV_ID, false);
            return;
        case HP_CLOSE:
            rocket->setValve(HP_ID, false);
            return;
        case LDR_CLOSE:
            rocket->setValve(LDR_ID, false);
            return;
        case FDR_CLOSE:
            rocket->setValve(FDR_ID, false);
            return;
        case LMV_CLOSE:
            rocket->setValve(LMV_ID, false);
            return;
        case FMV_CLOSE:
            rocket->setValve(FMV_ID, false);
            return;

        case IGN1_ON:
            rocket->setIgnitionOn(IGN1_ID, true);
            return;
        case IGN1_OFF:
            rocket->setIgnitionOn(IGN1_ID, false);
            return;
        case IGN2_ON:
            rocket->setIgnitionOn(IGN2_ID, true);
            return;
        case IGN2_OFF:
            rocket->setIgnitionOn(IGN2_ID, false);
            return;

        case PING_PI_ROCKET:
            // TODO ******************************* TODO
            // Timeout autovent logic

            static CAN_message_t msg;
            if(ALARA == PROP_NODE_ID) // prop node
                msg.id = PING_PROP_PI;
            else
                msg.id = PING_ENGINE_PI;
            Can0.write(msg);
            return;
        case ZERO_PTS:
            rocket->zeroPTs();
            rocket->testDelay();
            return;
    }
    return;

}
