#include "DelayedAction.h"

DelayedAction::DelayedAction(int time, functionPtr action)
    : timeToPerform(time), action(action), nextAction(nullptr) {};
    
/*
DelayedAction::DelayedAction(int time, void* action, int data, DelayedAction* nextAction)
    : timeToPerform(time), dataAction(action), data(data), nextAction(nextAction) {};
*/

void DelayedAction::performAction() {
    action(); }

void DelayedDataAction::performAction() {
    dataAction(data); }

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
    DelayedAction* currentAction = firstAction;
    while (currentAction->nextAction != nullptr || //go through list until nextTime >= newTime or next is null
           currentAction->nextAction->timeToPerform < newAction->timeToPerform)
    {
        currentAction = currentAction->nextAction;
    }
    newAction->nextAction = currentAction->nextAction; //insert new between current and next
    currentAction->nextAction = newAction;
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

/*
void DelayedAction::addAction(int time, functionPtr action)
{
    DelayedAction* newAction = new DelayedAction(time, action);
    if(firstAction == nullptr) //if there are no other actions, add this.
    {
        firstAction = newAction;
        return;
    }
    DelayedAction* currentAction = firstAction;
    while (currentAction->nextAction != nullptr || //go through list until nextTime >= newTime or next is null
           currentAction->nextAction->timeToPerform < newAction->timeToPerform)
    {
        currentAction = currentAction->nextAction;
    }
    newAction->nextAction = currentAction->nextAction; //insert new between current and next
    currentAction->nextAction = newAction;
}


void DelayedAction::addAction(int time, dataFunctionPtr action, int data)
{
    DelayedDataAction* newAction = new DelayedDataAction(time, action, data);
    if(firstAction == nullptr) //if there are no other actions, add this.
    {
        firstAction = newAction;
        return;
    }
    DelayedAction* currentAction = firstAction;
    while (currentAction->nextAction != nullptr || //go through list until nextTime >= newTime or next is null
           currentAction->nextAction->timeToPerform < newAction->timeToPerform)
    {
        currentAction = currentAction->nextAction;
    }
    newAction->nextAction = currentAction->nextAction; //insert new between current and next
    currentAction->nextAction = newAction;
}
*/
