#include <scheduler/ThreadPool.h> 

namespace scheduler {
ThreadPool::ThreadPool(size_t num_threads) : stop_(false){
    workers_.reserve(num_threads);
    for (size_t i=0; i<num_threads;i++){
        workers_.emplace_back(&ThreadPool::worker_loop,this);
    }
} 
/** 
 * destructor for graceful shutdown
 */

ThreadPool:: ~ThreadPool(){
    stop_=true;
    condition_.notify_all(); // Notify all worker threads to exit

    for(auto &worker:workers_){
        /**
         * join all threads
         */
        if(worker.joinable()){
            worker.join(); // Wait for all worker threads to finish
        }
    }

}
/**
 * submit a task to the threadpool 
 */

void ThreadPool::submit(Task task){
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        tasks_queue_.push(std::move(task)); // Add task to the queue
    }
    condition_.notify_one(); // Notify one worker thread that a new task is available
}

void ThreadPool::worker_loop(){
    while(true){
        Task task([]{});
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            condition_.wait(lock,[&]{
                return !tasks_queue_.empty() ||  stop_;
            });

            if(stop_ && tasks_queue_.empty()){
                return; // Exit the worker thread if the pool is stopping and there are no tasks left
            }

            task=std::move(tasks_queue_.top());
            tasks_queue_.pop(); // Remove the task from the queue
        }
        task();
    }
}

}

