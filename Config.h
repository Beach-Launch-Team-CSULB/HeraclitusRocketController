// 4/1/2024
#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string.h>
#include <cstdint>

// Constant defined for packing sensor data
#define NO_DECIMAL ((uint8_t) 100)

// Extern definitions for timing.
extern uint32_t ignitionTime;
extern uint32_t LMVOpenTime;
extern uint32_t FMVOpenTime;
extern uint32_t LMVCloseTime;
extern uint32_t FMVCloseTime;

#define UPPER_ALARA true //prop
//#undef UPPER_ALARA
//#define LOWER_ALARA true //engine
//#undef LOWER_ALARA

#define ENGN_NODE_ID 0
#define PROP_NODE_ID 1

// Valves & Igniters
#define NUM_VALVES 10
#define NUM_IGNITERS 2


// Vehicle Commands
#define ABORT      ((uint32_t) 0)
#define VENT       ((uint32_t) 1)
#define FIRE       ((uint32_t) 2)
#define TANK_PRESS ((uint32_t) 3)
#define HIGH_PRESS ((uint32_t) 4)
#define STANDBY    ((uint32_t) 5)
#define IGNITE     ((uint32_t) 6)  // ***NEW***
#define TEST       ((uint32_t) 7)

// Valve & Igniter (HPO Commands)
#define IGN1_OFF   ((uint32_t) 8)   // Igniter One
#define IGN1_ON    ((uint32_t) 9)

#define IGN2_OFF   ((uint32_t) 10)  // Igniter Two
#define IGN2_ON    ((uint32_t) 11)

#define HV_CLOSE   ((uint32_t) 12)  // High Vent valve
#define HV_OPEN    ((uint32_t) 13)

#define HP_CLOSE   ((uint32_t) 14)  // High Press valve
#define HP_OPEN    ((uint32_t) 15)

#define LDV_CLOSE  ((uint32_t) 16)  // Lox Dome Vent valve
#define LDV_OPEN   ((uint32_t) 17)

#define FDV_CLOSE  ((uint32_t) 18)  // Fuel Dome Vent valve
#define FDV_OPEN   ((uint32_t) 19)

#define LDR_CLOSE  ((uint32_t) 20)  // Lox Dome Reg valve
#define LDR_OPEN   ((uint32_t) 21)

#define FDR_CLOSE  ((uint32_t) 22)  // Fuel Dome Reg valve
#define FDR_OPEN   ((uint32_t) 23)

#define LV_CLOSE   ((uint32_t) 24)  // Lox Vent valve
#define LV_OPEN    ((uint32_t) 25)

#define FV_CLOSE   ((uint32_t) 26)  // Fuel Vent valve
#define FV_OPEN    ((uint32_t) 27)

#define LMV_CLOSE  ((uint32_t) 28)  // Lox Main valve
#define LMV_OPEN   ((uint32_t) 29)

#define FMV_CLOSE  ((uint32_t) 30)  // Fuel Main valve
#define FMV_OPEN   ((uint32_t) 31)

// Timing
#define SET_IGNITION     ((uint32_t) 32)  // Set ignition time for both igniters.
#define SET_LMV_OPEN     ((uint32_t) 33)  // Set LMV open time.
#define SET_FMV_OPEN     ((uint32_t) 34)  // Set FMV open time. 
#define SET_LMV_CLOSE    ((uint32_t) 35)  // Set LMV close time.
#define SET_FMV_CLOSE    ((uint32_t) 36)  // Set FMV close time.

#define GET_IGNITION     ((uint32_t) 37)  // Confirm ignition time for both igniters.
#define GET_LMV_OPEN     ((uint32_t) 38)  // Confirm LMV open time.
#define GET_FMV_OPEN     ((uint32_t) 39)  // Confirm FMV open time.
#define GET_LMV_CLOSE    ((uint32_t) 40)  // Confirm LMV close time.
#define GET_FMV_CLOSE    ((uint32_t) 41)  // Confirm FMV close time.

// Ping
#define PING_PI_ROCKET   ((uint32_t) 42)  // *Important*: Pi Box sends a ping to the rocket. 

// Reserved
#define RESERVED         ((uint32_t) 43)  // Reserved - Does nothing.

// PT Configuration
#define ZERO_PTS         ((uint32_t) 44)  // Zero the pressure transducers.

// State Reports
#define SR_PROP   ((uint32_t) 127)
#define SR_ENGINE ((uint32_t) 128)

// Sensor Reports
#define SENS_1_4_PROP     ((uint32_t) 129) // Lox High,   Fuel High, Lox Dome,   Fuel Dome
#define SENS_5_8_PROP     ((uint32_t) 130) // Lox Tank1,  Lox Tank2, Fuel Tank1, Fuel Tank2
#define SENS_9_12_ENGINE  ((uint32_t) 131) // Pneumatics, Lox Inlet, Fuel Inlet, Fuel Injector
#define SENS_13_16_ENGINE ((uint32_t) 132) // Chamber1,   Chamber2,  UNUSED,     UNUSED

// Timing Reports
#define SEND_IGNITION     ((uint32_t) 133)  // ALARA response to 37. Sends igniter time for confirmation.
#define SEND_LMV_OPEN     ((uint32_t) 134)  // ALARA response to 38. Sends LMV open time for confirmation. 
#define SEND_FMV_OPEN     ((uint32_t) 135)  // ALARA response to 39. Sends FMV open time for confirmation.
#define SEND_LMV_CLOSE    ((uint32_t) 136)  // ALARA response to 40. Sends LMV close time for confirmation.
#define SEND_FMV_CLOSE    ((uint32_t) 137)  // ALARA response to 41. Sends FMV close time for confirmation.

// Ping Response
#define PING_PROP_PI      ((uint32_t) 138)
#define PING_ENGINE_PI    ((uint32_t) 139)
#define OP_MSG_PROP       ((uint32_t) 140)
#define OP_MSG_ENGINE     ((uint32_t) 141)





// Data Direction Inputs 
#define INPUT  (uint32_t)0
#define OUTPUT (uint32_t)1



// Igniter Digital Pin Designations and IDs | ALARA LOWER 

#define IGN1_ID         (uint32_t)10  // Igniter A / ENG-IGNA / ALARA Lower
#define IGN1_PIN_DIG    (uint32_t)83  //ALARA: DIG5 | Teensy 3.6 MCU Pin: PTC16
#define IGN1_PIN_PWM    (uint32_t)2 


#define IGN2_ID         (uint32_t)11  // Igniter B / ENG-IGNB
#define IGN2_PIN_DIG    (uint32_t)81  // ALARA: DIG5 | Teensy 3.6 MCU Pin: PTC14
#define IGN2_PIN_PWM    (uint32_t)10  // In Dan's Code they are both 2?  
      

// Valve Digital Pin Designations and IDs | ALARA LOWER 

#define HP_ID           (uint32_t)20  // High Press valve / SV HI PRES  
#define HP_PIN_DIG      (uint32_t)87  // ALARA: DIG1 | Teensy 3.6 MCU Pin: PTD10
#define HP_PIN_PWM      (uint32_t)5

#define HV_ID           (uint32_t)21  // High Vent valve / SV HI PRES V 
#define HV_PIN_DIG      (uint32_t)86  // ALARA: DIG2 | Teensy 3.6 MCU Pin: PTC19
#define HV_PIN_PWM      (uint32_t)6

#define FMV_ID          (uint32_t)22  // Fuel Main valve / SV MV FUEL 
#define FMV_PIN_DIG     (uint32_t)85  // ALARA: DIG3 | Teensy 3.6 MCU Pin: PTC18
#define FMV_PIN_PWM     (uint32_t)8  

#define LMV_ID          (uint32_t)23  // Lox Main valve / SV MV LOX
#define LMV_PIN_DIG     (uint32_t)84  // ALARA: DIG4 | Teensy 3.6 MCU Pin: PTC17
#define LMV_PIN_PWM     (uint32_t)7

// Valve Digital Pin Designations and IDs | ALARA UPPER 

#define LV_ID           (uint32_t)24  // Lox Vent valve / SV LOX V
#define LV_PIN_DIG      (uint32_t)87  // ALARA: DIG1 | Teensy 3.6 MCU Pin: PTD10
#define LV_PIN_PWM      (uint32_t)5

#define LDV_ID          (uint32_t)25  // Lox Dome Vent valve / SV DREG L
#define LDV_PIN_DIG     (uint32_t)84  // ALARA: DIG3 | Teensy 3.6 MCU Pin: PTC18
#define LDV_PIN_PWM     (uint32_t)7

#define LDR_ID          (uint32_t)26  // Lox Dome Reg valve / SV DREG LV
#define LDR_PIN_DIG     (uint32_t)85  // ALARA: DIG4 | Teensy 3.6 MCU Pin: PTC17
#define LDR_PIN_PWM     (uint32_t)8

#define FV_ID           (uint32_t)27  // Fuel Vent valve / SV FUEL V 
#define FV_PIN_DIG      (uint32_t)83  // ALARA: DIG5 | Teensy 3.6 MCU Pin: PTC16
#define FV_PIN_PWM      (uint32_t)2

#define FDV_ID          (uint32_t)28  // Fuel Dome Vent valve / SV DREG F V 
#define FDV_PIN_DIG     (uint32_t)80  // ALARA: DIG7 | Teensy 3.6 MCU Pin: PTC14
#define FDV_PIN_PWM     (uint32_t)9

#define FDR_ID          (uint32_t)29  // Fuel Dome Reg valve /  SV DREG F
#define FDR_PIN_DIG     (uint32_t)81  // ALARA: DIG8 | Teensy 3.6 MCU Pin: PTC13
#define FDR_PIN_PWM     (uint32_t)10



// Pressure Transducer Sesnor Pin Designations, IDs, and Calibration Values
// (sensors are currently uncalibrated)

//Upper Prop Node:
#define PT_LOX_HIGH_ID          (1<<0) //00000000 00000001  Upper A22
#define PT_LOX_HIGH_PIN         A21
#define PT_LOX_HIGH_CAL_M       13.3f
#define PT_LOX_HIGH_CAL_B       -618.0f

#define PT_FUEL_HIGH_ID         (1<<1) //00000000 00000010  Upper A21
#define PT_FUEL_HIGH_PIN        A22
#define PT_FUEL_HIGH_CAL_M      17.2f
#define PT_FUEL_HIGH_CAL_B      -632.0f

#define PT_LOX_DOME_ID          (1<<2) //00000000 00000100  Upper A3
#define PT_LOX_DOME_PIN         A3
#define PT_LOX_DOME_CAL_M       3.45f
#define PT_LOX_DOME_CAL_B       -143.0f

#define PT_FUEL_DOME_ID         (1<<3) //00000000 00001000  Upper A2
#define PT_FUEL_DOME_PIN        A2
#define PT_FUEL_DOME_CAL_M      3.33f
#define PT_FUEL_DOME_CAL_B      -123.0f

#define PT_LOX_TANK_1_ID        (1<<4) //00000000 00010000  Upper A14
#define PT_LOX_TANK_1_PIN       A14
#define PT_LOX_TANK_1_CAL_M     3.5f
#define PT_LOX_TANK_1_CAL_B     -131.0f

#define PT_LOX_TANK_2_ID        (1<<5) //00000000 00100000  Upper A11
#define PT_LOX_TANK_2_PIN       A11
#define PT_LOX_TANK_2_CAL_M     3.5f
#define PT_LOX_TANK_2_CAL_B     -134.0f

#define PT_FUEL_TANK_1_ID       (1<<6) //00000000 01000000  Upper A15
#define PT_FUEL_TANK_1_PIN      A15
#define PT_FUEL_TANK_1_CAL_M    3.33f
#define PT_FUEL_TANK_1_CAL_B    -126.0f

#define PT_FUEL_TANK_2_ID       (1<<7) //00000000 10000000  Upper A10
#define PT_FUEL_TANK_2_PIN      A10
#define PT_FUEL_TANK_2_CAL_M    3.36f
#define PT_FUEL_TANK_2_CAL_B    -125.0f

//Lower Engine Node:
#define PT_PNUEMATICS_ID        (1<<8) //00000001 00000000  Lower A15
#define PT_PNUEMATICS_PIN       A15
#define PT_PNUEMATICS_CAL_M     3.41f
#define PT_PNUEMATICS_CAL_B     -121.0f

#define PT_LOX_INLET_ID         (1<<9) //00000010 00000000  Lower A21
#define PT_LOX_INLET_PIN        A21
#define PT_LOX_INLET_CAL_M      3.41f
#define PT_LOX_INLET_CAL_B      -129.0f

#define PT_FUEL_INLET_ID        (1<<10) //00000100 00000000  Lower A22
#define PT_FUEL_INLET_PIN       A22
#define PT_FUEL_INLET_CAL_M     3.32f
#define PT_FUEL_INLET_CAL_B     -120.0f

#define PT_FUEL_INJECTOR_ID     (1<<11) //00001000 00000000  Lower A14
#define PT_FUEL_INJECTOR_PIN    A14
#define PT_FUEL_INJECTOR_CAL_M  3.39f
#define PT_FUEL_INJECTOR_CAL_B  -118.0f

#define PT_CHAMBER_1_ID         (1<<12) //00010000 00000000  Lower A10
#define PT_CHAMBER_1_PIN        A10
#define PT_CHAMBER_1_CAL_M      3.39f
#define PT_CHAMBER_1_CAL_B      -126.0f

#define PT_CHAMBER_2_ID         (1<<13) //00100000 00000000  Lower A11
#define PT_CHAMBER_2_PIN        A11
#define PT_CHAMBER_2_CAL_M      3.41f
#define PT_CHAMBER_2_CAL_B      -106.0f

//Prop Node Initialization Information
#ifdef UPPER_ALARA
    #define ALARA 1
//#define UPPER_SENSOR_ARRAY_DECL  {PT_LOX_HIGH_ID, 

    #define VALVE_ARRAY_LENGTH 6
    #define VALVE_ARRAY {LV_ID, LDV_ID, LDR_ID, FV_ID, FDV_ID, FDR_ID}

    #define SENSOR_ARRAY_LENGTH 8
    #define SENSOR_ARRAY {PT_LOX_HIGH_ID, PT_FUEL_HIGH_ID, PT_LOX_DOME_ID, PT_FUEL_DOME_ID, PT_LOX_TANK_1_ID, PT_LOX_TANK_2_ID, PT_FUEL_TANK_1_ID, PT_FUEL_TANK_2_ID}
    
    #define IGNITER_ARRAY_LENGTH 0
    #define IGNITER_ARRAY {}
#endif UPPER_ALARA

//Engine Node Initialization Information
#ifdef LOWER_ALARA
    #define ALARA 0

    #define VALVE_ARRAY_LENGTH 4
    #define VALVE_ARRAY {HP_ID, HV_ID, FMV_ID, LMV_ID}

    #define SENSOR_ARRAY_LENGTH 6
    #define SENSOR_ARRAY {PT_PNUEMATICS_ID, PT_LOX_INLET_ID, PT_FUEL_INLET_ID, PT_FUEL_INJECTOR_ID, PT_CHAMBER_1_ID, PT_CHAMBER_2_ID}
    
    #define IGNITER_ARRAY_LENGTH 2
    #define IGNITER_ARRAY {IGN1_ID, IGN2_ID}
#endif LOWER_ALARA

/*****************************************CAN DBC (Database File)****************************************
 *
 *       *Note: Out of 2048 unique CAN ids only 25 have been used so far (~1%).
 *       **Note: If we need unique ids for the Engine node this number will increase.
 *
 *
 *       Vehicle Commands:
 *
 *
 *       id      meaning
 *
 *       0       Abort
 *       1       Vent
 *       2       Fire
 *       3       Tank Press 
 *       4       High Press
 *       5       Standby
 *       6       Passive
 *       7       Test
 * 
 *
 *       Igniter/Valve (High Power Object) Commands:
 *
 *
 *       id      meaning
 *
 *        8      IGN1_OFF   (Igniter1)
 *        9      IGN1_ON    (Igniter1)
 * 
 *       10      IGN2_OFF   (Igniter2)
 *       11      IGN2_ON    (Igniter2)
 *       
 *       12      HV_CLOSE   (High Vent Valve)
 *       13      HV_OPEN    (High Vent Valve)
 * 
 *       14      HP_CLOSE   (High Press Valve)
 *       15      HP_OPEN    (High Press Valve)
 * 
 *       16      LDV_CLOSE  (Lox Dome Vent Valve)
 *       17      LDV_OPEN   (Lox Dome Vent Valve)      
 * 
 *       18      FDV_CLOSE  (Fuel Dome Vent Valve)
 *       19      FDV_OPEN   (Fuel Dome Vent Valve)
 * 
 *       20      LDR_CLOSE  (Lox Dome Reg Valve)
 *       21      LDR_OPEN   (Lox Dome Reg Valve)
 * 
 *       22      FDR_CLOSE  (Fuel Dome Reg Valve)
 *       23      FDR_OPEN   (Fuel Dome Reg Valve)
 * 
 *       24      LV_CLOSE   (Lox Vent Valve)
 *       25      LV_OPEN    (Lox Vent Valve)
 * 
 *       26      FV_CLOSE   (Fuel Vent Valve)
 *       27      FV_OPEN    (Fuel Vent Valve)
 * 
 *       28      LMV_CLOSE  (Lox Main Valve)
 *       29      LMV_OPEN   (Lox Main Valve)
 * 
 *       30      FMV_CLOSE  (Fuel Main Valve)
 *       31      FMV_OPEN   (Fuel Main Valve)
 * 
 * 
 *
 *       List of Sensors:
 *
 *       *Note: Order subject to change.
 *
 *       #1      PT High Lox Side
 *       #2      PT High Fuel Side
 *       #3      PT Lox Dome
 *       #4      PT Fuel Dome
 * 
 *       #5      PT Lox Tank 1
 *       #6      PT Lox Tank 2
 *       #7      PT Fuel Tank 1
 *       #8      PT Fuel Tank 2
 * 
 *       #9      PT Pneumatics
 *       #10     PT Lox Inlet
 *       #11     PT Fuel Inlet
 *       #12     PT Fuel Injector
 * 
 *       #13     PT Chamber 1
 *       #14     PT Chamber 2
 *       #15     _________________
 *       #16     _________________
 *
 *       *Note: The timestamp in frame 127 could be used to monitor the speed of the CAN bus during operation 
 *              (by adding a received timestamp from the CAN clock - they should be synched). If the group decides 
 *              that we do not need this data - then it could be filled with data for two of the sensors.
 * 
 *       **Note: After CAN FD has been implemented we could do something like: 127, 129, and 130 = propReport
 *                                                                             128, 131, and 132 = engineReport  
 *
 *
 *       id      meaning
 *
 *       127     State Report: Timestamp, Vehicle State, Valve State, and Pyro States from Propulsion Node.
 *       128     State Report: Timestamp, Vehicle State, Valve State, and Pyro States from Engine Node.
 *
 *       129     Sensors   1,  2,  3, and 4 from Propulsion Node.
 *       130     Sensors   5,  6,  7, and 8 from Propulsion Node.
 *       131     Sensors   9, 10, 11, and 12 from Propulsion Node.
 *       132     Sensors  13, 14, 15, and 16 from Propulsion Node.
 *
 *       *Check with someone to see if these are even necessary 
 *        (I think they're the same sensors for each node - the only thing that varies is the high power output channels):
 *       133     Sensors  1,  2,  3, and 4 from Engine Node.
 *       134     Sensors  5,  6,  7, and 8 from Engine Node.
 *       135     Sensors  9, 10, 11, and 12 from Engine Node.
 *       136     Sensors 13, 14, 15, and 16 from Engine Node.
 */

#endif