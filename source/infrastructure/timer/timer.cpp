#include "timer.h"

// the number of ticks of the processor from its start
std::chrono::high_resolution_clock::time_point timer::Now()
{
    return std::chrono::high_resolution_clock::now();
}

// difference in milliseconds
long long timer::ElapsedMs(const std::chrono::high_resolution_clock::time_point start, const std::chrono::high_resolution_clock::time_point end)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}