#pragma once
#include "interfaces/i_sort_algorithm.h"

class QuickSortAlgorithm : public ISort
{
    int32_t Partition(std::vector<int32_t>& data, int32_t low, int32_t high);
    void    QuickSortRecursive(std::vector<int32_t>& data, int32_t low, int32_t high);

public:
    SortResult Sort(std::vector<int32_t>& data) override;
    [[nodiscard]] std::string GetName() const override;
};
