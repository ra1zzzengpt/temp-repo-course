#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "models/sort_result.h"

class ISort
{
protected:
    uint64_t comparisons_ = 0;
    uint64_t swaps_ = 0;

    void ResetCounters() { comparisons_ = 0; swaps_ = 0; }

public:
    virtual ~ISort() = default;

    virtual SortResult Sort(std::vector<int32_t>& data) = 0;

    virtual std::string GetName() const = 0;

    [[nodiscard]] uint64_t GetComparisons() const { return comparisons_; }
    [[nodiscard]] uint64_t GetSwaps()       const { return swaps_; }
};
