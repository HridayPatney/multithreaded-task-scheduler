#include "scheduler/Task.h"

namespace scheduler {
    Task::Task(TaskFn fn)
        :function_(std::move(fn)) {}// Move the function to avoid unnecessary copying

        /* 
we dont do function_=fn because
std::function can be expensive to copy

std::move transfers ownership efficiently

This avoids unnecessary allocations.*/

    void Task::execute() {
        function_();
    }
} // namespace scheduler 
