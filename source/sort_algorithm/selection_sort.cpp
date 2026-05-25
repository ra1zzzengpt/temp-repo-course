#include "selection_sort.h"
#include "utils/timer.h"

std::string SelectionSortAlgorithm::GetName() const { return "Selection sort"; }

SortResult SelectionSortAlgorithm::Sort(std::vector<int32_t>& data)
{
    SortResult result;
    result.algorithm_name = GetName();
    ResetCounters();

    if (data.empty())
    {
        result.completed = false;
        result.message = "Empty";
        return result;
    }

    const auto start = timer::Now();

    for (size_t i = 0; i < data.size() - 1; i++)
    {
        size_t max_idx = i;
        for (size_t j = i + 1; j < data.size(); j++)
        {
            comparisons_++;
            if (data[j] > data[max_idx]) max_idx = j;
        }
        if (max_idx != i)
        {
            std::swap(data[i], data[max_idx]);
            swaps_++;
        }
    }

    result.elapsed_ms = timer::ElapsedMs(start, timer::Now());
    result.comparisons = comparisons_;
    result.swaps = swaps_;
    return result;
}
