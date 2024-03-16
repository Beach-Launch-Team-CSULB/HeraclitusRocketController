#include "extendedIO.h"

// Extended Digital Port Map Definitions
const ED_MAP ed_map[30] = 
{
    {ED_PORT_1,ED_BIT_1},
    {ED_PORT_2,ED_BIT_2},
    {ED_PORT_3,ED_BIT_3},
    {ED_PORT_4,ED_BIT_4},
    {ED_PORT_5,ED_BIT_5},
    {ED_PORT_6,ED_BIT_6},
    {ED_PORT_7,ED_BIT_7},
    {ED_PORT_8,ED_BIT_8},
    {ED_PORT_9,ED_BIT_9},
    {ED_PORT_10,ED_BIT_10},
    {ED_PORT_11,ED_BIT_11},
    {ED_PORT_12,ED_BIT_12},
    {ED_PORT_13,ED_BIT_13},
    {ED_PORT_14,ED_BIT_14},
    {ED_PORT_15,ED_BIT_15},
    {ED_PORT_16,ED_BIT_16},
    {ED_PORT_17,ED_BIT_17},
    {ED_PORT_18,ED_BIT_18},
    {ED_PORT_19,ED_BIT_19},
    {ED_PORT_20,ED_BIT_20},
    {ED_PORT_21,ED_BIT_21},
    {ED_PORT_22,ED_BIT_22},
    {ED_PORT_23,ED_BIT_23},
    {ED_PORT_24,ED_BIT_24},
    {ED_PORT_25,ED_BIT_25},
    {ED_PORT_26,ED_BIT_26},
    {ED_PORT_27,ED_BIT_27},
    {ED_PORT_28,ED_BIT_28},
    {ED_PORT_29,ED_BIT_29},
    {ED_PORT_30,ED_BIT_30}
};

// Extended Digital PinMode - Based on Port letter and Port Bit Number
void pinMode(char register_letter, uint8_t register_bit, bool data_direction)
{
  // Find the correct pin control register based on the register letter and pin
  uint32_t PCR = 0x40049000 + (register_letter - 'A') * 0x1000 + register_bit*4;
  // set the pin control register to the PCR mux
  (*(volatile uint32_t *)PCR) = PORT_PCR_MUX(0x1);

  // Set the data direction register based on the data_direction input
  uint32_t PDDR = 0x400FF014 + (register_letter - 'A') * 0x40;
  if(data_direction) // Flip data direction bit to 1 (OUTPUT)
  { (*(volatile uint32_t *)PDDR) |= (1 << register_bit); }
  else // Flip data direction bit to 0 (INPUT)
  { (*(volatile uint32_t *)PDDR) &= !(1 << register_bit); }
}

void digitalWrite(char register_letter, uint8_t register_bit, bool data)
{
  if(data)
  {       
    uint32_t PSOR = 0x400FF004 + (register_letter - 'A') * 0x40;
    (*(volatile uint32_t *)PSOR) = (1<<register_bit);
  }
  else
  {
    uint32_t PCOR = 0x400FF008 + (register_letter - 'A') * 0x40;
    (*(volatile uint32_t *)PCOR) = (1<<register_bit);
  }
}

bool digitalRead(char register_letter, uint8_t register_bit)
{
  uint32_t PDIR = 0x400FF010 + (register_letter - 'A') * 0x40;
  return (*(volatile uint32_t *)PDIR)>>register_bit;
}

void pinMode(ED_MAP pin_ed_map, bool data_direction)
{
  pinMode(pin_ed_map.ed_port,pin_ed_map.ed_bit,data_direction);
}

void digitalWrite(ED_MAP pin_ed_map, bool data)
{
  digitalWrite(pin_ed_map.ed_port,pin_ed_map.ed_bit,data); 
}

bool digitalRead(ED_MAP pin_ed_map)
{
  return digitalRead(pin_ed_map.ed_port,pin_ed_map.ed_bit);
}

void pinModeExtended(uint8_t pin, bool data_direction)
{
  if(pin<=57) // Teensy pin designations
  {
    pinMode(pin,data_direction);
  }
  else // Extended pin designations
  {
    uint8_t ed_pin_index = pin-ED_PIN_1;
    pinMode(ed_map[ed_pin_index],data_direction);
  }
}

void digitalWriteExtended(uint8_t pin, bool data)
{
  if(pin<=57) // Teensy pin designations
  {
    digitalWrite(pin,data);
  }
  else // Extended pin designations
  {
    uint8_t ed_pin_index = pin-ED_PIN_1;
    digitalWrite(ed_map[ed_pin_index],data);
  }
}

bool digitalReadExtended(uint8_t pin)
{
  if(pin<=57) // Teensy pin designations
  {
    return digitalRead(pin);
  }
  else // Extended pin designations
  {
    uint8_t ed_pin_index = pin-ED_PIN_1;
    return digitalRead(ed_map[ed_pin_index]);
  }
}