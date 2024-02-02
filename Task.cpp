#include "Task.h"

Task::Task(std::string name, int id, State state, int priority = 0)
    :name(name),
    state(state),
    priority(priority), 
    id(id)
    { }

std::string Task::getName() const {
    return name;
}

int Task::getId() const {
    return id;
}

State Task::getState() const {
    return state;
}

int Task::getPriority() const {
    return priority;
}

void Task::setState(State state) {
    this->state = state;
}

void Task::setPriority(int priority) {
    this->priority = priority;
}

