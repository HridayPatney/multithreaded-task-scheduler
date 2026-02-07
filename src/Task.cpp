#include "scheduler/Task.h"

namespace scheduler {

Task:: Task(std:: function<void()> func, int priority)
    : func_(std::move(func)),priority_(priority){}

void Task::operator()() const {
    func_();  // executes the stored function 
}

int Task:: priority() const{
    return priority_;
}


}