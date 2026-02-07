#include <iostream>
#include <thread>
#include "scheduler/ThreadPool.h"

int main() {
    scheduler::ThreadPool pool(4);

    for (int i = 0; i < 10; ++i) {
        pool.submit(scheduler::Task([i] {
            std::cout << "Task " << i
                      << " running on thread "
                      << std::this_thread::get_id()
                      << std::endl;
        },10-i));
    }

    return 0;
}
