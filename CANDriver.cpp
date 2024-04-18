// 4/2/2024
#include "CANDriver.h"
#include "Config.h"

#include <FlexCAN.h>
#include <string>

/* To-do: 
 *        1.) Ensure that the NO_DECIMAL addition is working correctly.
 *        2.) Test the final byte of sendStateReport by actuating a valve.
 */


CANDriver::CANDriver()
{
  // 
};

uint32_t CANDriver::readMessage()
{
  CAN_message_t msg;
  // Initialized as an unused id.
  msg.id = 255;
  Can0.read(msg);

  // Check for instances where we need to read the data field.
  uint32_t time = 0;
  if(msg.len == 4)
  {
    /*
    std::string num1 = std::to_string(msg.buf[0]);
    std::string num2 = std::to_string(msg.buf[1]);
    std::string num3 = std::to_string(msg.buf[2]);
    std::string num4 = std::to_string(msg.buf[3]);
    std::string num5 = std::to_string(msg.buf[4]);
    time = stoi(num1<<8 + (num2<<8 +num3+num4+num5);
    */
   time = (((msg.buf[0])*256+msg.buf[1])*256+msg.buf[2])*256+msg.buf[3];

    if(msg.id == SET_IGNITION)
    {
      ignitionTime = time;
    }
    if(msg.id == SET_LMV_OPEN)
    {
      LMVOpenTime = time;
    }
    if(msg.id == SET_FMV_OPEN)
    {
      FMVOpenTime = time;
    }
    if(msg.id == SET_LMV_CLOSE)
    {
      LMVCloseTime = time;
    }
    if(msg.id == SET_FMV_CLOSE)
    {
      FMVCloseTime = time;
    }
  }

  return msg.id;
}

void CANDriver::sendStateReport(int time, uint8_t rocketState, Rocket node, bool Prop)
{
  CAN_message_t msg;
  msg.flags.extended = 0;
  msg.flags.remote = 0;
  msg.len = 6;
  int aTime = time;
  
  char* littleElf;
  littleElf =  (char*)&aTime;
  msg.buf[0] = littleElf[3];
  msg.buf[1] = littleElf[2];
  msg.buf[2] = littleElf[1];
  msg.buf[3] = littleElf[0];

  // If it is passed in as one of the defines in the Config.h that would be best. If not we can adjust it here.
  msg.buf[4]= rocketState;

  // Determine which ALARA to generate the report for.
  // Use stoi() for valve/igniter states. For both nodes the first two numbers in the byte will be zeros.
  // You can use the ultraElf since you are only dealing with one byte. Otherwise the littleElf would need to help.
  std::string ultraElf = "00";
  if (Prop == 0)
  {
    msg.id = SR_ENGINE;
    // Get HP, HV, FMV, LMV, IGN1, IGN2.
    // You could make this faster by looping through the valve/igniter maps using an iterator and bit shifting, but this .___Read() 
    // has already been built so I will use it along with the ternary operator.
    char hp   = (node.valveRead(HP_ID)      ? '1' : '0');
    char hv   = (node.valveRead(HV_ID)      ? '1' : '0');
    char fmv  = (node.valveRead(FMV_ID)     ? '1' : '0');
    char lmv  = (node.valveRead(LMV_ID)     ? '1' : '0');
    char ign1 = (node.ignitionRead(IGN1_ID) ? '1' : '0');
    char ign2 = (node.ignitionRead(IGN2_ID) ? '1' : '0');

    ultraElf = ultraElf + hp + hv + fmv + lmv + ign1 + ign2;

    // Cast as a single byte before packing into the frame.
    msg.buf[5] = uint8_t(stoi(ultraElf, nullptr, 2));
  }
  else
  {
    msg.id = SR_PROP;
    // Get LV, LDV, LDR, FV, FDV, FDR.
    char lv  = (node.valveRead(LV_ID)  ? '1' : '0');
    char ldv = (node.valveRead(LDV_ID) ? '1' : '0');
    char ldr = (node.valveRead(LDR_ID) ? '1' : '0');
    char fv  = (node.valveRead(FV_ID)  ? '1' : '0');
    char fdv = (node.valveRead(FDV_ID) ? '1' : '0');
    char fdr = (node.valveRead(FDR_ID) ? '1' : '0');

    ultraElf = ultraElf + lv + ldv + ldr + fv + fdv + fdr;

    // Cast as a single byte before packing into the frame.
    msg.buf[5] = uint8_t(stoi(ultraElf, nullptr, 2));
  }

  Can0.write(msg);
};

void CANDriver::sendSensorData(int sensorID, float sensorData1, float sensorData2, float sensorData3, float sensorData4)
{
  CAN_message_t msg;
  msg.id = sensorID;  // Ensure CAN id corresponds to the correct sensor ids.
  msg.flags.extended = 0;
  msg.flags.remote = 0;
  msg.len = 8;
  
  // Avoiding dealing with the binary representation of floats. Divide by ten on CANReceive.py end.
  sensorData1 *= NO_DECIMAL;
  int sensorData1Mod = sensorData1;
  sensorData2 *= NO_DECIMAL;
  int sensorData2Mod = sensorData2;
  sensorData3 *= NO_DECIMAL;
  int sensorData3Mod = sensorData3;
  sensorData4 *= NO_DECIMAL;
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