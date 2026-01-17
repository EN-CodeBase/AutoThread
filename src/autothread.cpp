#include "autothread.hpp"


template<typename Rep, typename Period, typename F, typename... Args>
AutoThread::AutoThread(std::chrono::duration<Rep, Period> latency,
            F&& f,
            Args&&... args)
{
    worker = std::thread(
        [this,
            latency,
            fn = std::forward<F>(f),
            tup = std::make_tuple(std::forward<Args>(args)...)]() mutable
        {
            while (running.load(std::memory_order_relaxed)) {
                std::apply(fn, tup);
                std::this_thread::sleep_for(latency);
            }
        }
    );
}


void AutoThread::Kill(){
    running.store(false);
    if (worker.joinable())
        worker.join();
}

AutoThread::~AutoThread() {
    Kill();
}