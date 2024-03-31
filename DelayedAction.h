/**
 * Implementation of DelayedAction for Heraclitus
 * 
 * Heraclitus requires a system to handle events at a specific time.
 * Using Delay() works for debugging, but it will lead to problems
 * when the program needs to collect sensor data and perform other
 * asynchronous tasks. Arduino doesn't natively handle this.
 * 
 * DelayedAction utilizes a LinkedList system that is sorted in the
 * order they will be executed. A DelayedAction can be created simply
 * by calling addAction with the time and a function pointer. Somewhere
 * within loop() a call to peroformActions with the current time in millis
 * will ensure that all DelayedActions will be executed if their time allows.
 * 
 * Data is an optional input that will add the integer, often a valveID, as
 * a parameter for its function.
 */

typedef void(*functionPtr)();
typedef void(*dataFunctionPtr)(int);

class DelayedAction
{
    //friend class DelayedDataAction;
    
    protected:
    static DelayedAction* firstAction;

    int timeToPerform;
    functionPtr action;
    DelayedAction* nextAction;

    DelayedAction(int, functionPtr);
    void performAction();
    static void addActionHelper(DelayedAction*);

    public:
    static void performActions(int);
    static void addAction(int, functionPtr);
    static void addAction(int, dataFunctionPtr, int);
};

class DelayedDataAction : DelayedAction
{
    friend class DelayedAction;

    protected: 
    int data;
    dataFunctionPtr dataAction;

    DelayedDataAction(int, dataFunctionPtr, int);
    void performAction();
};