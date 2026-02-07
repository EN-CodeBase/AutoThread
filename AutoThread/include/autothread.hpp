#pragma once

#include <iostream>
#include <Windows.h>
#include <chrono>

#include <thread>
#include <atomic>
#include <type_traits>

#include <utility>
#include <tuple>

using namespace std::chrono_literals;
/*
    what autothred does

    it is a thread that handles itself
    you can run a function within it
    it has a forced delay between runs
*/

template <typename ReturnType = bool>
struct AutoThread {

    std::atomic<bool> running{false};
    std::thread SelfThread;

    std::atomic<int> CallTimes{};

    // if given void type, make output have bool type 
    using Type = std::conditional_t<std::is_void_v<ReturnType>, bool, ReturnType>;
    std::atomic<Type> output{};

    template<typename Rep, typename Period, typename F, typename... Args>
    AutoThread(std::chrono::duration<Rep, Period> latency,
               F&& f,
               Args&&... args);

    void Kill();
    ~AutoThread();
};

template <typename ReturnType>
template<typename Rep, typename Period, typename F, typename... Args>
AutoThread<ReturnType>::AutoThread(std::chrono::duration<Rep, Period> latency,
                                   F&& f,
                                   Args&&... args)
{

    using Ret = std::invoke_result_t<F, Args...>;

    auto func = std::forward<F>(f);

    // IMPORTANT: preserve correct argument types
    auto tup = std::tuple<std::decay_t<Args>...>(std::forward<Args>(args)...);

    running.store(true);

    SelfThread = std::thread(
        [this, latency, func, tup]() mutable
        {
            using Clock = std::chrono::steady_clock;
            auto next = Clock::now();
            auto ns_latency = std::chrono::duration_cast<std::chrono::nanoseconds>(latency);
            LARGE_INTEGER li;

            HANDLE timer = CreateWaitableTimerEx(
                nullptr,
                nullptr,
                CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
                TIMER_ALL_ACCESS
            );

            while (running.load())
            {
                next += ns_latency;

                auto now = Clock::now();
                auto wait_ns =
                    std::chrono::duration_cast<std::chrono::nanoseconds>(next - now).count();

                if (wait_ns < 0)
                    wait_ns = 0;

                li.QuadPart = -static_cast<LONGLONG>(wait_ns / 100);

                SetWaitableTimerEx(
                    timer,
                    &li,
                    0,
                    nullptr,
                    nullptr,
                    nullptr,
                    0
                );

                WaitForSingleObject(timer, INFINITE);

                if constexpr (std::is_void_v<Ret>) {
                    std::apply(func, tup);
                } else {
                    output.store(std::apply(func, tup));
                }

                CallTimes.store(CallTimes.load() + 1);
            }

            CancelWaitableTimer(timer);
            CloseHandle(timer);
        }
    );
}

template <typename ReturnType>
void AutoThread<ReturnType>::Kill()
{
    running.store(false);

    if (SelfThread.joinable()) {
        SelfThread.join();
        // std::cout << "Killd after: " << CallTimes.load() << " Times\n";
    }
}

template <typename ReturnType>
AutoThread<ReturnType>::~AutoThread()
{
    Kill();
}
