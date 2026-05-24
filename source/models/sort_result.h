#pragma once

#include <string>
#include <cstdint>

struct SortResult
{
    std::string algorithm_name;
    uint64_t comparisons = 0;
    uint64_t swaps = 0;
    long long elapsed_ms = 0;
    bool completed = true;
    std::string message;

    [[nodiscard]] std::string ToString() const
    {
        if (!completed) return algorithm_name + " | " + message;
        return algorithm_name + " | comparisons: " + std::to_string(comparisons) +
               " | swaps: " + std::to_string(swaps) +
               " | " + std::to_string(elapsed_ms) + " ms";
    }
};
