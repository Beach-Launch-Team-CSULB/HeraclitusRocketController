#include "DelayedAction.h"

DelayedAction* DelayedAction::firstAction = nullptr;
Rocket* DelayedAction::myRocket = nullptr;

DelayedAction::DelayedAction(int time, functionPtr action)
    : timeToPerform(time), action(action), nextAction(nullptr) {};
    

DelayedDataAction::DelayedDataAction(int time, dataFunctionPtr action, int data)
    : DelayedAction(time, nullptr), dataAction(action), data(data) {};


void DelayedAction::init(Rocket* rocket)
{
    myRocket = rocket; 
}

void DelayedAction::performAction() {
    (myRocket->*action)(); }

void DelayedDataAction::performAction() {
    (myRocket->*dataAction)(data); }


void DelayedAction::performActions(int currentTime)
{
    DelayedAction* currentAction = firstAction;
    while(currentAction != nullptr)
    {
        if(currentTime >= currentAction->timeToPerform)
        {
            currentAction->performAction();
            firstAction = currentAction->nextAction;
            delete currentAction;

            currentAction = currentAction->nextAction;
        }
        else
            return;
    }
    return;
}

void DelayedAction::addActionHelper(DelayedAction* newAction)
{
    if(firstAction == nullptr) //if there are no other actions, add this.
    {
        firstAction = newAction;
        return;
    }
    DelayedAction* actionIterator = firstAction;
    while (actionIterator->nextAction != nullptr && //go through list until nextTime >= newTime or next is null
           actionIterator->nextAction->timeToPerform < newAction->timeToPerform)
    {
        actionIterator = actionIterator->nextAction;
    }
    newAction->nextAction = actionIterator->nextAction; //insert new between iterator and next
    actionIterator->nextAction = newAction;
}

void DelayedAction::addAction(int time, functionPtr action)
{
    DelayedAction* newAction = new DelayedAction(time, action);
    addActionHelper(newAction);
}

void DelayedAction::addAction(int time, dataFunctionPtr action, int data)
{
    DelayedDataAction* newAction = new DelayedDataAction(time, action, data);
    addActionHelper(newAction);
}
