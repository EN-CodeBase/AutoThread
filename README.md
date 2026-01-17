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

      AutoThread Thrd (
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

## Usage
call the constructor which takes the following parameters:
- latency (chrono syntax): ex 300ms
- function (lambda, method or a function) with void return
- function parameters


## Installation
This library does NOT use any third party libraries so as long as you have cpp 17+ installed it should work  
Recomended to use cmake for ease of use

## Limitations 
- cant handle reference parameters
- passed function cant return anything other than void
