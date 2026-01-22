#pragma once
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <tuple>
#include <utility>

using namespace std::chrono_literals;

template <typename ReturnType>
class AutoThread {
    std::thread worker;
    std::atomic<bool> running{true};

public:
    template<typename Rep, typename Period, typename F, typename... Args>
    AutoThread(std::chrono::duration<Rep, Period> latency,
               F&& f,
               Args&&... args);


    void Kill();

    ~AutoThread();

};
