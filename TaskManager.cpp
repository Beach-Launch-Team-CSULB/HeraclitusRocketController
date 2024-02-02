#include "TaskManager.h"

TaskManager::TaskManager()
{}

int TaskManager::getSize() const{
    return this->taskQueue.size();
}

Task TaskManager::getFront() const{
    return this->taskQueue.front()
} 

void TaskManager::pushTask(Task task) {
    this->taskQueue.push(task);
}

void TaskManager::popTask() {
    this->taskQueue.pop();
}

