#pragma once 
#define _GLIBCXX_HAS_GTHREADS 1

#include <vector> 
#include <thread> 
#include <queue> 
#include <mutex> 
#include <condition_variable>

#include <atomic> 

#include "scheduler/Task.h"


namespace scheduler {

struct TaskCompare {
    bool operator()(const Task&a, const Task& b) const {
        return a .priority() < b.priority();
    }
};

class ThreadPool{
public:
    explicit ThreadPool(size_t num_threads);
    ~ThreadPool();

    void submit(Task task);
private:
    void worker_loop(); // Worker thread function

    std::vector<std::thread> workers_; // Vector to hold worker threads

    std:: priority_queue<Task,std:: vector<Task>, TaskCompare> tasks_queue_; // priority Queue to hold tasks

    std::mutex queue_mutex_; // Mutex to protect access to the task queue

    std::condition_variable condition_; // Condition variable for task notification

    std::atomic<bool> stop_; // Flag to indicate when to stop the thread pool
};
}


