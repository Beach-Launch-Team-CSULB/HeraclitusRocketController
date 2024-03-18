// Mapping from pin to {bit offset, port}
// Port A = 0 ... D = 3
std::map<int, std::array<int, 2>> pinMap = {
    {IGN1_PIN_DIG,{16, 2}},  
    {IGN2_PIN_DIG,{14,2}},
    {HP_PIN_DIG,{10,2}},
    {HV_PIN_DIG,{19,2}},
    {FMV_PIN_DIG,{18,2}},
    {LMV_PIN_DIG,{17,2}},
    {LV_PIN_DIG,{10,3}},
    {LDV_PIN_DIG,{8,2}},
    {LDR_PIN_DIG,{17,2}},
    {FV_PIN_DIG,{16,2}},
    {FDV_PIN_DIG,{14,2}},
    {FDR_PIN_DIG,{13,2}}
};

// Base register addresses
// Used to calculate target register
std::map<std::string, uint32_t> baseRegs = {
    {"PCR", 0x40049000},
    {"PCOR", 0x400FF048},
    {"PSOR", 0x400FF044},
    {"PDDR", 0x400FF014}
};

void ExtendedIO::pinModeExtended(int pin, int isGPIO, int dataDirection) {
    /*  Argument 1: Pin # designation specified on the ALARA V2.x MCU Pin Map and gets the address 
        Argument 2: Specifies if this is a General Purpose Input/Output pin or not 
        Manually writes to Registers that define given pin behaviors
    */
    
    volatile uint32_t* PCR = digitalPinToPort(pin,PCR);     // Gets the exact address of the pin control register
    *PCR |= (isGPIO << 8);                                  // Sets pin PCR to GPIO Mode, 0 is INPUT, 1 is OUTPUT

    volatile uint32_t* PDDR = digitalPinToPort(pin, PDDR);  // Gets the exact address of the Port Data Direction Register
    int PDDR_Offset = digitalPinToBit(pin)                  // Gets bit offset for PDDR Register 
    *PDDR |= (dataDirection << PDDR_Offset);                // Sets pin PDDR to dataDirection Value at correct bit offset
}

void ExtendedIO::digitalWriteExtended(int pin, int value) {
    /*  Argument 1: Pin # designation specified on the ALARA V2.x MCU Pin Map and gets the address 
        Argument 2: 1 High, 0 Low
        Manually Writes Commands to Ports, Pinmode must be set prior
    */
    int pinBitOffset = digitalPinToBit(pin);                    // Gets bit offset for both PCOR & PSOR Register 
    if (value == 0){  // Clear port to 0: Low
        volatile uint32_t* PCOR = digitalPinToPort(pin,PCOR);   // Gets the exact address of the Port Clear Output Register
        *PCOR |= (0 << pinBitOffset);                           // Sets pin PCOR to 0 (Low) at correct bit offset
    }
    if (value == 1){  // Sets port to 1: High
        volatile uint32_t* PSOR = digitalPinToPort(pin,PSOR);   // Gets the exact address of the Port Set Output Register
        *PSOR |= (1 << pinBitOffset);                           // Sets pin PSOR to 1 (High) at correct bit offset
    }

int ExtendedIO::digitalPinToBit(int pin) {
    offset = pinMap[pin][0];
    if (offset == pinMap.end()) return -1;
    return offset;
}

int ExtendedIO::digitalPinToPort(int pin) {
    port = pinMap[pin][1];
    if (port == pinMap.end()) return -1;
    return port;
}

uint32_t ExtendedIO::fetchRegister(int pin, Register_Name reg) {
    register = baseRegs[reg];
    pin = digitalPinToPort(pin);
    port = digitalPinToBit(pin);
    if (register == baseRegs.end() || pin == -1  || port == -1) return -1;
    if (register == "PCR") return volatile uint32_t (register + pin * 0x1000 + port * 4);
    else return volatile uint32_t (register + 0x40 * pin);
}