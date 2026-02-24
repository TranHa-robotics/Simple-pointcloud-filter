#pragma once

#include <chrono>
#include <iostream>
#include <string>

namespace PCP
{

    struct Timer
    {
        std::string name;
        std::chrono::high_resolution_clock::time_point start;

        Timer(const std::string &n) : name(n), start(std::chrono::high_resolution_clock::now()) {}

        // Destructor tu dong chay khi ra khoi block
        ~Timer()
        {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> ms = end - start;
            std::cout << "[" << name << "] Runtime: " << ms.count() << " ms\n";
        }
    };
}
