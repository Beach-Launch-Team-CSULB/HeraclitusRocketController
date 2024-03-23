// 2/10/2024

//#include <Arduino.h>
#include <FlexCAN.h>
#include "CANDriver.h"
#include "Config.h"
#include "Igniter.h"
#include "Valve.h"

/* To-do: 
 *        1.) Research remote flag.
 */


CANDriver::CANDriver()
{
  // 
};

uint32_t CANDriver::readMessage()
{
  static CAN_message_t msg;
  // Initialized as an unused id.
  msg.id = 255;
  Can0.read(msg);

  return msg.id;
}

void CANDriver::sendStateReport(int time, uint8_t rocketState, Valve valves[], Igniter igniters[], bool Prop)
{
  static CAN_message_t msg;
  msg.flags.extended = 0;
  // msg.flags.remote = 0; <---- Do we need this?
  msg.len = 8;
  int aTime = time;
  
  char* littleElf;
  littleElf =  (char*)&aTime;
  msg.buf[0] = littleElf[3];
  msg.buf[1] = littleElf[2];
  msg.buf[2] = littleElf[1];
  msg.buf[3] = littleElf[0];

  // Determine which ALARA to generate the report for.
  if (Prop == true)
    msg.id = SR_PROP;
  else
    msg.id = SR_ENGINE;

  // If it is passed in as one of the defines in the Config.h that would be best. If not we can adjust it here.
  msg.buf[4]= rocketState;

  // First byte of valve states.
  uint8_t byte5 = 0;
  for(int x = 0; x < 2; x++)
  {
      byte5 = byte5|valves[x].getValveOpen() << x;
  }
  msg.buf[5] = byte5;

  // Second byte of valve states.
  uint8_t byte6 = 0;
  for(int x = 2; x < 10; x++)
  {
      byte6 = byte6|valves[x].getValveOpen() << (x-2);
  }
  msg.buf[6] = byte6;

  // Byte of igniter states.
  uint8_t byte7 = 0;
  for(int x = 0; x < 2; x++)
  {
      byte7 = byte7|igniters[x].getIgniterOn() << x;
  }
  msg.buf[7] = byte7;

  Can0.write(msg);
};

void CANDriver::sendSensorData(int sensorID, float sensorData1, float sensorData2, float sensorData3, float sensorData4)
{
  static CAN_message_t msg;
  msg.id = sensorID;  // Ensure CAN id corresponds to the correct sensor ids.
  msg.flags.extended = 0;
  // msg.flags.remote = 0; <---- Do we need this?
  msg.len = 8;
  
  // Avoiding dealing with the binary representation of floats. Divide by ten on CANReceive.py end.
  sensorData1 *= 100;
  int sensorData1Mod = sensorData1;
  sensorData2 *= 100;
  int sensorData2Mod = sensorData2;
  sensorData3 *= 100;
  int sensorData3Mod = sensorData3;
  sensorData4 *= 100;
  int sensorData4Mod = sensorData4;
  
  char* littleElf;
  littleElf =  (char*)&sensorData1Mod;
  msg.buf[0] = littleElf[1];
  msg.buf[1] = littleElf[0];
  littleElf =  (char*)&sensorData2Mod;
  msg.buf[2] = littleElf[1];
  msg.buf[3] = littleElf[0];
  littleElf =  (char*)&sensorData3Mod;
  msg.buf[4] = littleElf[1];
  msg.buf[5] = littleElf[0];
  littleElf =  (char*)&sensorData4Mod;
  msg.buf[6] = littleElf[1];
  msg.buf[7] = littleElf[0];

  Can0.write(msg);
};