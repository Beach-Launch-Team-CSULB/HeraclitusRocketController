#ifndef VEHICLE_STATE
#define VEHICLE_STATE
enum VehicleState{
    TEST,               // All Igniter and Valves Controllable 
    PASSIVE,            // Everything
    STANDBY,
    HIGH_PRESS,
    TANK_PRESS,
    FIRE,
    VENT,
    ABORT
};

#endif