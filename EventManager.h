#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <string>
#include <queue>
#include "Event.h"

class EventManager {
public:
    EventManager();
    int getSize() const;
    void pushEvent(Event event);
    void popEvent();
    Event getFront() const;
private:
    std::queue<Event> taskQueue;
};



#endif // EventManager_H