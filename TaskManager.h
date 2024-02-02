#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <string>
#include <queue>
#include "Task.h"

class TaskManager {
public:
    TaskManager();
    int getSize() const;
    void pushTask(Task task);
    void popTask();
    Task getFront() const;
private:
    std::queue<Task> taskQueue;
};



#endif // TASKMANAGER_H