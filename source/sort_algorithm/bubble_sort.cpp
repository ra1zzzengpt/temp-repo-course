#include "bubble_sort.h"
#include "utils/timer.h"
#include <utility>

std::string BubbleSortAlgorithm::GetName() const { return "Bubble sort"; }

SortResult BubbleSortAlgorithm::Sort(std::vector<int32_t>& data)
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

    for (size_t i = 0; i < data.size(); i++)
    {
        bool swapped = false;
        for (size_t j = 0; j < data.size() - 1 - i; j++)
        {
            comparisons_++;
            if (data[j] < data[j + 1])
            {
                std::swap(data[j], data[j + 1]);
                swaps_++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    result.elapsed_ms = timer::ElapsedMs(start, timer::Now());
    result.comparisons = comparisons_;
    result.swaps = swaps_;
    return result;
}
