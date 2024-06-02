// 4/16/2024
#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string.h>
#include <cstdint>

// Constant defined for packing sensor data
#define NO_DECIMAL ((uint8_t) 1000)


// LEDs
#define LED0 0
#define LED1 1


// Extern definitions for timing.
extern uint32_t ignitionTime;
extern uint32_t LMVOpenTime;
extern uint32_t FMVOpenTime;
extern uint32_t LMVCloseTime;
extern uint32_t FMVCloseTime;


// Extern definitions for zeroing.
extern uint32_t zeroPTOne;
extern uint32_t zeroPTTwo;
extern uint32_t zeroPTThree;
extern uint32_t zeroPTFour;
extern uint32_t zeroPTFive;
extern uint32_t zeroPTSix;
extern uint32_t zeroPTSeven;
extern uint32_t zeroPTEight;

extern bool calibIsM;
extern float calibVal;
extern uint8_t sensorCalibID;


// Valves & Igniters
#define NUM_VALVES 10
#define NUM_IGNITERS 2

// Propulsion is 1.
// Engine is 0.

#define ALARA_ID 0

// Constant define for specifying the number of times per second sensor data & state reports are to be transmitted over CAN (ms).
#define CAN_INTERVAL ((uint32_t) 333)

// Vehicle Commands
#define ABORT      ((uint32_t) 0)
#define VENT       ((uint32_t) 1)
#define FIRE       ((uint32_t) 2)
#define TANK_PRESS ((uint32_t) 3)
#define HIGH_PRESS ((uint32_t) 4)
#define STANDBY    ((uint32_t) 5)
#define IGNITE     ((uint32_t) 6)
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
#define MANUAL_OVERRIDE  ((uint32_t) 43)

// PT Configuration
#define ZERO_PTS                      ((uint32_t) 44)  // Zero the pressure transducers.

#define GET_M_VAL                     ((uint32_t) 45)
#define SET_M_VAL                     ((uint32_t) 46)
#define GET_B_VAL                     ((uint32_t) 47)
#define SET_B_VAL                     ((uint32_t) 48)

#define START_SD_LOG                  ((uint32_t) 49)



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

// PT Calib. Response to "Get" request from GUI
#define SEND_M_VAL         ((uint32_t) 142)
#define SEND_B_VAL         ((uint32_t) 143)



// Igniter Digital Pin Designations and IDs | ALARA LOWER 

#define IGN1_ID         (uint32_t)4  // Igniter A / ENG-IGNA / ALARA Lower
#define IGN1_PIN_DIG    (uint32_t)28  //ALARA: DIG5 | Teensy 3.6 MCU Pin: PTC16
#define IGN1_PIN_PWM    (uint32_t)28 


#define IGN2_ID         (uint32_t)5  // Igniter B / ENG-IGNB
#define IGN2_PIN_DIG    (uint32_t)29  // ALARA: DIG5 | Teensy 3.6 MCU Pin: PTC14
#define IGN2_PIN_PWM    (uint32_t)29  // In Dan's Code they are both 2?  
      

// Valve Digital Pin Designations and IDs | ALARA LOWER 

#define HP_ID           (uint32_t)7  // High Press valve / SV HI PRES  
#define HP_PIN_DIG      (uint32_t)2  // ALARA: DIG1 | Teensy 3.6 MCU Pin: PTD10
#define HP_PIN_PWM      (uint32_t)2

#define HV_ID           (uint32_t)6  // High Vent valve / SV HI PRES V 
#define HV_PIN_DIG      (uint32_t)3  // ALARA: DIG2 | Teensy 3.6 MCU Pin: PTC19
#define HV_PIN_PWM      (uint32_t)3

#define FMV_ID          (uint32_t)15  // Fuel Main valve / SV MV FUEL 
#define FMV_PIN_DIG     (uint32_t)4  // ALARA: DIG3 | Teensy 3.6 MCU Pin: PTC18
#define FMV_PIN_PWM     (uint32_t)4  

#define LMV_ID          (uint32_t)14  // Lox Main valve / SV MV LOX
#define LMV_PIN_DIG     (uint32_t)5  // ALARA: DIG4 | Teensy 3.6 MCU Pin: PTC17
#define LMV_PIN_PWM     (uint32_t)5

// Valve Digital Pin Designations and IDs | ALARA UPPER 

#define LV_ID           (uint32_t)12  // Lox Vent valve / SV LOX V
#define LV_PIN_DIG      (uint32_t)6  // ALARA: DIG1 | Teensy 3.6 MCU Pin: PTD10
#define LV_PIN_PWM      (uint32_t)6

#define LDV_ID          (uint32_t)8  // Lox Dome Vent valve / SV DREG L
#define LDV_PIN_DIG     (uint32_t)7  // ALARA: DIG3 | Teensy 3.6 MCU Pin: PTC18
#define LDV_PIN_PWM     (uint32_t)7

#define LDR_ID          (uint32_t)10  // Lox Dome Reg valve / SV DREG LV
#define LDR_PIN_DIG     (uint32_t)8  // ALARA: DIG4 | Teensy 3.6 MCU Pin: PTC17
#define LDR_PIN_PWM     (uint32_t)8

#define FV_ID           (uint32_t)13  // Fuel Vent valve / SV FUEL V 
#define FV_PIN_DIG      (uint32_t)9  // ALARA: DIG5 | Teensy 3.6 MCU Pin: PTC16
#define FV_PIN_PWM      (uint32_t)9

#define FDV_ID          (uint32_t)9  // Fuel Dome Vent valve / SV DREG F V 
#define FDV_PIN_DIG     (uint32_t)10  // ALARA: DIG7 | Teensy 3.6 MCU Pin: PTC14
#define FDV_PIN_PWM     (uint32_t)10

#define FDR_ID          (uint32_t)11  // Fuel Dome Reg valve /  SV DREG F
#define FDR_PIN_DIG     (uint32_t)11  // ALARA: DIG8 | Teensy 3.6 MCU Pin: PTC13
#define FDR_PIN_PWM     (uint32_t)11



// Pressure Transducer Sesnor Pin Designations, IDs, and Calibration Values

//Upper Prop Node:
#define PT_LOX_HIGH_ID          ((uint8_t) 0)
#define PT_LOX_HIGH_PIN         A0
#define PT_LOX_HIGH_CAL_M       0.0956f
#define PT_LOX_HIGH_CAL_B       -615.0f

#define PT_FUEL_HIGH_ID         ((uint8_t) 1)
#define PT_FUEL_HIGH_PIN        A1
#define PT_FUEL_HIGH_CAL_M      0.0939f
#define PT_FUEL_HIGH_CAL_B      -614.0f

#define PT_LOX_DOME_ID          ((uint8_t) 2)
#define PT_LOX_DOME_PIN         A2
#define PT_LOX_DOME_CAL_M       0.0197f
#define PT_LOX_DOME_CAL_B       -143.0f

#define PT_FUEL_DOME_ID         ((uint8_t) 3)
#define PT_FUEL_DOME_PIN        A3
#define PT_FUEL_DOME_CAL_M      0.0191f
#define PT_FUEL_DOME_CAL_B      -123.0f

#define PT_LOX_TANK_1_ID        ((uint8_t) 4)
#define PT_LOX_TANK_1_PIN       A4
#define PT_LOX_TANK_1_CAL_M     0.02f
#define PT_LOX_TANK_1_CAL_B     -131.0f

#define PT_LOX_TANK_2_ID        ((uint8_t) 5)
#define PT_LOX_TANK_2_PIN       A5
#define PT_LOX_TANK_2_CAL_M     0.02f
#define PT_LOX_TANK_2_CAL_B     -134.0f

#define PT_FUEL_TANK_1_ID       ((uint8_t) 6)
#define PT_FUEL_TANK_1_PIN      A6
#define PT_FUEL_TANK_1_CAL_M    0.0191f
#define PT_FUEL_TANK_1_CAL_B    -126.0f

#define PT_FUEL_TANK_2_ID       ((uint8_t) 7)
#define PT_FUEL_TANK_2_PIN      A7
#define PT_FUEL_TANK_2_CAL_M    0.0192f
#define PT_FUEL_TANK_2_CAL_B    -125.0f

//Lower Engine Node:
#define PT_PNUEMATICS_ID        ((uint8_t) 8)
#define PT_PNUEMATICS_PIN       A8
#define PT_PNUEMATICS_CAL_M     0.0195f
#define PT_PNUEMATICS_CAL_B     -121.0f

#define PT_LOX_INLET_ID         ((uint8_t) 9)
#define PT_LOX_INLET_PIN        A9
#define PT_LOX_INLET_CAL_M      0.0195f
#define PT_LOX_INLET_CAL_B      -129.0f

#define PT_FUEL_INLET_ID        ((uint8_t) 10)
#define PT_FUEL_INLET_PIN       A10
#define PT_FUEL_INLET_CAL_M     0.019f
#define PT_FUEL_INLET_CAL_B     -120.0f

#define PT_FUEL_INJECTOR_ID     ((uint8_t) 11)
#define PT_FUEL_INJECTOR_PIN    A11
#define PT_FUEL_INJECTOR_CAL_M  0.0194f
#define PT_FUEL_INJECTOR_CAL_B  -118.0f

#define PT_CHAMBER_1_ID         ((uint8_t) 12)
#define PT_CHAMBER_1_PIN        A12
#define PT_CHAMBER_1_CAL_M      0.0194f
#define PT_CHAMBER_1_CAL_B      -126.0f

#define PT_CHAMBER_2_ID         ((uint8_t) 13)
#define PT_CHAMBER_2_PIN        A13
#define PT_CHAMBER_2_CAL_M      0.0195f
#define PT_CHAMBER_2_CAL_B      -106.0f

#define LED_PIN_1              ((uint8_t) 33)
#define LED_PIN_2              ((uint8_t) 34)
#define LED_PIN_3              ((uint8_t) 35)           

#endif