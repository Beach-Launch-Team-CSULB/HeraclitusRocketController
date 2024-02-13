#include "CANDriver.h"

CANDriver::CANDriver() {
    Can0.begin();
}

int CANDriver::readMessage() {
    CAN_message_t msg;
    Can0.read(msg);
    return msg.id;
}