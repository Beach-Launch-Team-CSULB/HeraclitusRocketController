// 2/10/2024

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
#define PASSIVE    ((uint32_t) 6)
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

// State Reports
#define SR_PROP   ((uint32_t) 127)
#define SR_ENGINE ((uint32_t) 128)

// Sensor Reports
#define SENS_1_4_PROP   ((uint32_t) 129)
#define SENS_5_8_PROP   ((uint32_t) 130)
#define SENS_9_12_PROP  ((uint32_t) 131)
#define SENS_13_16_PROP ((uint32_t) 132)

#define SENS_1_4_ENGINE   ((uint32_t) 133)
#define SENS_5_8_ENGINE   ((uint32_t) 134)
#define SENS_9_12_ENGINE  ((uint32_t) 135)
#define SENS_13_16_ENGINE ((uint32_t) 136)

// Valve & Igniter Pin #s and IDs, 
// all on Alara HP Channel 2

#define IGN1_ID         10  // Igniter A / ENG-IGNA
#define IGN1_Pin_WTE    5
#define IGN1_Pin_GRN    26

#define IGN2_ID         11  // Igniter B / ENG-IGNB
#define IGN2_Pin_RED    7 
#define IGN2_Pin_BLK    27

#define HV_ID           20  // High Vent valve / SV HI PRES V 
#define HV_Pin_RED      3    
#define HV_Pin_BLK      21

#define HP_ID           21  // High Press valve / SV HI PRES  
#define HP_Pin_RED      2
#define HP_Pin_BLK      20

#define LDV_ID          22  // Lox Dome Vent valve / SV DREG LV
#define LDV_PIN_RED     10
#define LDV_PIN_BLK     28

#define FDV_ID          23  // Fuel Dome Vent valve / SV DREG F V 
#define FDV_PIN_RED     
#define PIN_RED          

#define LDR_ID          24  // Lox Dome Reg valve / SV DREG LV 
#define LDR_PIN_RED     5
#define PIN_RED    

#define FDR_ID          25  // Fuel Dome Reg valve /  SV DREG F
#define FDR_PIN_RED     
#define PIN_RED    

#define LV_ID           26  // Lox Vent valve / SV LOX V
#define LV_PIN_RED
#define PIN_RED     

#define FV_ID           27  // Fuel Vent valve / SV FUEL V 
#define FV_PIN_RED
#define PIN_RED        

#define LMV_ID          28  // Lox Main valve / SV MV LOX
#define LMV_PIN_RED
#define PIN_RED          

#define FMV_ID          29  // Fuel Main valve / SV MV FUEL 
#define PIN_RED     



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
 *       #3      PT Lox Tank 1
 *       #4      PT Lox Tank 2
 * 
 *       #5      PT Fuel Tank 1
 *       #6      PT Fuel Tank 2
 *       #7      PT Lox Dome
 *       #8      PT Fuel Dome
 * 
 *       #9      PT Fuel Inlet
 *       #10     PT Fuel Injector
 *       #11     PT Lox Inlet
 *       #12     PT Main Pneumatics
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