enum VehicleState{
    // These state names will change - DERK
    // These can be renamed to more descriptive varibale names so long as the names known to derek/teamlead's understading 
    IDLE,                       // The Rocket is doing nothing
    MANUAL,                     // All commands are accepted, no control logic, limited safety logic
    
    //THESE STATES ALL OCCUR UNDER AUTOSEQUENCE,    Loading Fuel, sensors on, valves off, ignier off, locks off control, only step forward in a series of commands, chain
    FUELLOADING,                //testidle, teststart, 
    PRESSURIZATION,             //Solenoid Valve puts pressuized nitrogen into vehicle, Dangerous Phase 
    PROPELLENT_PRESSURIZATION,  //Valves open and let in pressurize tanks from high pressure section, very dangerous  
    FIRESTATE,                  //need to countdown from t-15, we start the 2nd interval timer to launch, once timers are up, turn on igniter, valve these need to be sequenced properly, hard deadlock state checking for ABORT
    
    //Timing data needed to be stored in a separate file so poper timing data is correct
    PERGE,                      //optional, dump everything in tanks, just main valves 
    HOLD,                       // Hold everything so that some of the gas gets kept, 

    //Safety Phases - derk's idea 
    VENT,                       // Main valves empty, every valve open 
    ABORT,                      // Stop Timers and Close all valves 
    OXIDIZER_DUMP,              // Empty out oxidizer tank
    FUEL_DUMP                     // Empty out fuel tank 
};