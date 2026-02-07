#pragma once  // tells the compiler that include this header file only once per compilation unit

#include <functional> // for std:: function which allows storing any callable: lambda, function, functor 

#include<atomic>

namespace scheduler { // start of scheduler namespace
class Task { // abstracts a unit of work
public:
    Task(std::function<void()> func, int priority=0);
    // constructor above takes the actual unit of work (func), and a priority which is 0 by default
    void operator()() const; // makes task callable like a function 
    // this object can be called like a function , it takes no arguments, returns nothing and does not modify the object 
    int priority() const; //exposes priority safely and makes it read only
    
private: 
    std:: function<void()> func_; // stores the tasks executable logic 
    // its type erased so its flexible 
    int priority_;
};
} 

