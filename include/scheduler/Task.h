#pragma once  // tells the compiler that include this header file only once per compilation unit

#include <functional> // for std:: function

namespace scheduler { // start of scheduler namespace
class Task {
public:
    using TaskFn = std ::function<void()>;

    explicit Task(TaskFn fn);

    void execute();
private: 
    TaskFn function_; // Encapsulation: Users can’t modify the function after submission Thread-safety is preserved
};

} //

