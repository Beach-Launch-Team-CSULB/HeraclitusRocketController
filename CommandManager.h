#include "Rocket.h"
#include "CANDriver.h"

class CommandManager
{
    private: 
        static Rocket* rocket;
        static CANDriver* comSystem;

    public: 
        static void init(Rocket*, CANDriver*);
        static void checkCommand();

};