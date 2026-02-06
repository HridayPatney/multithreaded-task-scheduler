#pragma one 

#include <vector> 
#include<thread> 
#include <queue> 
#include <mutex> 
#include <condition_variable>
#include<condition_variable>
#include<atomic> 

#include "scheduler/Task.h"


namespace scheduler {

class ThreadPool{
public:
    explicit ThreadPool(size_t num_threads);
    ~ThreadPool();

    void submit(Task task);
private:
    void worker(); // Worker thread function

    std::vector<std::thread> workers_; // Vector to hold worker threads

    std::queue<Task> tasks_queue_; // Queue to hold tasks

    std::mutex queue_mutex_; // Mutex to protect access to the task queue

    std::condition_variable cv_; // Condition variable for task notification

    std::atomic<bool> running_; // Flag to indicate when to stop the thread pool
}
}


