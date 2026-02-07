# AutoThread
A C++ class which allows you to easely make and manage multithreading in your program

## Overview
this library allows you to easely multithread functions and programs  
It removes all the boilerplate of working with threads in C++ and allows for easy handling of them  

## Features
- Auto-Running     | the function specified will start imidietly running
- Latency          | you can specify a latency for the thread
- Infinite Runtime | unless program terminates or thread is killed
- Thread Killing   | Thread.Kill() ends the thread after the last function call finishes

      #include "AutoThread/include/autothread.hpp"

      AutoThread<ReturnType> Thrd (
        500ms
        /* Function */
        [](int x, int y){
            cout << x + y << endl;
        },
        /* Params */
        1, 2
      };

      // if not specified, latency is preset to 10ms
      AutoThread Thrd_2 (
        /* Function */
        [](int x, int y){
            cout << x * y << endl;
        },
        /* Params */
        1, 2
      };

      // sleeps the main thread
      this_thread::sleep_for(1s);

      Thrd.Kill();
      // Thrd_2 will be killed (joined) automatically when the program terminates

        Thrd.Output.load() // gives you the output of the thread
        Thrd.CallTimes.load() // gives you the number of times thread colled function

## Usage
call the constructor which takes the following parameters:
- latency (chrono syntax): ex 300ms
- function (lambda, method or a function) with ReturnType return
- function parameters


## Installation
Copy and paste library or header file into project
Reference the library in CMake file via: AutoThread/lib/cmake/AutoThread/AutoThreadTargets.cmake

## Limitations 
- cant handle reference parameters
- cant change function variables during thread runtime
- cant have non primitive return type
- not good error handling (CAREFUL, if big compiler error check if you gave proper inputs to AutoThread)
