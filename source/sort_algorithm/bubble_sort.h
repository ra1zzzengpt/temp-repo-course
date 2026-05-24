#pragma once
#include "interfaces/i_sort_algorithm.h"

class BubbleSortAlgorithm : public ISort
{
public:
    SortResult Sort(std::vector<int32_t>& data) override;
    [[nodiscard]] std::string GetName() const override;
};
