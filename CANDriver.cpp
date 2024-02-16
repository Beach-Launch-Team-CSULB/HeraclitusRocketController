// 2/10/2024

//#include <Arduino.h>
#include <FlexCAN.h>
#include "CANDriver.h"
#include "Config.h"
#include "Igniter.h"
#include "Valve.h"

/* To-do: 
 *        1.) Make array of valve and igniter pointers - that way the objects themselves are not being passed each time.
 *        2.) Determine if CANBus must be passed as a reference. (Figure out if constructor will work.)
 *        3.) Combine this with Analicia's constructor, read, and sendOperatorMessage functions.
 */

/* Try this first - may need to be moved into main. 
CANDriver::CANDriver()
{
  Can0.begin(500000);
};
*/

void CANDriver::sendStateReport(int time, uint8_t rocketState, Valve valves[], Igniter igniters[], bool Prop)
{
  CAN_message_t msg;
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
  CAN_message_t msg;
  msg.id = sensorID;  // Ensure CAN id corresponds to the correct sensor ids.
  
  // Avoiding dealing with the binary representation of floats. Divide by ten on CANReceive.py end.
  sensorData1 *= 10;
  int sensorData1Mod = sensorData1;
  sensorData2 *= 10;
  int sensorData2Mod = sensorData2;
  sensorData3 *= 10;
  int sensorData3Mod = sensorData3;
  sensorData4 *= 10;
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