#pragma once
#include <Arduino.h>

// Extended Digital Pin Definitions (original definitions)
#define ED1 'E',6
#define ED2 'E',7
#define ED3 'E',8
#define ED4 'E',9
#define ED5 'E',12
#define ED6 'E',27
#define ED7 'E',28
#define ED8 'A',4
#define ED9 'A',6
#define ED10 'A',7
#define ED11 'A',8
#define ED12 'A',9
#define ED13 'A',10
#define ED14 'A',11
#define ED15 'A',24
#define ED16 'A',25
#define ED17 'A',27
#define ED18 'B',6
#define ED19 'B',7
#define ED20 'B',8
#define ED21 'B',9
#define ED22 'C',12
#define ED23 'C',13
#define ED24 'C',14
#define ED25 'C',15
#define ED26 'C',16
#define ED27 'C',17
#define ED28 'C',18
#define ED29 'C',19
#define ED30 'D',10

// Extended Digital Pin Designations
enum ED_PIN : const uint8_t
{
    ED_PIN_1 = 58,
    ED_PIN_2 = 59,
    ED_PIN_3 = 60,
    ED_PIN_4 = 61,
    ED_PIN_5 = 62,
    ED_PIN_6 = 63,
    ED_PIN_7 = 64,
    ED_PIN_8 = 65,
    ED_PIN_9 = 66,
    ED_PIN_10 = 67,
    ED_PIN_11 = 68,
    ED_PIN_12 = 69,
    ED_PIN_13 = 70,
    ED_PIN_14 = 71,
    ED_PIN_15 = 72,
    ED_PIN_16 = 73,
    ED_PIN_17 = 74,
    ED_PIN_18 = 75,
    ED_PIN_19 = 76,
    ED_PIN_20 = 77,
    ED_PIN_21 = 78,
    ED_PIN_22 = 79,
    ED_PIN_23 = 80,
    ED_PIN_24 = 81,
    ED_PIN_25 = 82,
    ED_PIN_26 = 83,
    ED_PIN_27 = 84,
    ED_PIN_28 = 85,
    ED_PIN_29 = 86,
    ED_PIN_30 = 87
};

// Extended Digital Port Register Bit
enum ED_BIT : const uint8_t
{
    ED_BIT_1 = 6,
    ED_BIT_2 = 7,
    ED_BIT_3 = 8,
    ED_BIT_4 = 9,
    ED_BIT_5 = 12,
    ED_BIT_6 = 27,
    ED_BIT_7 = 28,
    ED_BIT_8 = 4,
    ED_BIT_9 = 6,
    ED_BIT_10 = 7,
    ED_BIT_11 = 8,
    ED_BIT_12 = 9,
    ED_BIT_13 = 10,
    ED_BIT_14 = 11,
    ED_BIT_15 = 24,
    ED_BIT_16 = 25,
    ED_BIT_17 = 27,
    ED_BIT_18 = 6,
    ED_BIT_19 = 7,
    ED_BIT_20 = 8,
    ED_BIT_21 = 9,
    ED_BIT_22 = 12,
    ED_BIT_23 = 13,
    ED_BIT_24 = 14,
    ED_BIT_25 = 15,
    ED_BIT_26 = 16,
    ED_BIT_27 = 17,
    ED_BIT_28 = 18,
    ED_BIT_29 = 19,
    ED_BIT_30 = 10
};

// Extended Digital Port Letter
enum ED_PORT : const char
{
    ED_PORT_1 = 'E',
    ED_PORT_2 = 'E',
    ED_PORT_3 = 'E',
    ED_PORT_4 = 'E',
    ED_PORT_5 = 'E',
    ED_PORT_6 = 'E',
    ED_PORT_7 = 'E',
    ED_PORT_8 = 'A',
    ED_PORT_9 = 'A',
    ED_PORT_10 = 'A',
    ED_PORT_11 = 'A',
    ED_PORT_12 = 'A',
    ED_PORT_13 = 'A',
    ED_PORT_14 = 'A',
    ED_PORT_15 = 'A',
    ED_PORT_16 = 'A',
    ED_PORT_17 = 'A',
    ED_PORT_18 = 'B',
    ED_PORT_19 = 'B',
    ED_PORT_20 = 'B',
    ED_PORT_21 = 'B',
    ED_PORT_22 = 'C',
    ED_PORT_23 = 'C',
    ED_PORT_24 = 'C',
    ED_PORT_25 = 'C',
    ED_PORT_26 = 'C',
    ED_PORT_27 = 'C',
    ED_PORT_28 = 'C',
    ED_PORT_29 = 'C',
    ED_PORT_30 = 'D'
};

// Extended Digital Port Map Structure
struct ED_MAP
{
public:
    ED_PORT ed_port;
    ED_BIT ed_bit;
};

void pinMode(char register_letter, uint8_t register_bit, bool data_direction);
void digitalWrite(char register_letter, uint8_t register_bit, bool data);
bool digitalRead(char register_letter, uint8_t register_bit);

void pinMode(ED_MAP pin_ed_map, bool data_direction);
void digitalWrite(ED_MAP pin_ed_map, bool data);
bool digitalRead(ED_MAP pin_ed_map);

void pinModeExtended(uint8_t pin, bool data_direction);
void digitalWriteExtended(uint8_t pin, bool data);
bool digitalReadExtended(uint8_t pin);