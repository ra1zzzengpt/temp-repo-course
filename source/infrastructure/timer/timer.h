#pragma once
#include <chrono>

namespace timer
{
    std::chrono::high_resolution_clock::time_point Now();
    long long ElapsedMs(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end);
}