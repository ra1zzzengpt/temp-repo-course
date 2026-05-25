#include "quick_sort.h"
#include "utils/timer.h"

std::string QuickSortAlgorithm::GetName() const { return "Quick sort"; }

int32_t QuickSortAlgorithm::Partition(std::vector<int32_t>& data,
    const int32_t low, const int32_t high)
{
    const int32_t pivot = data[high];
    int32_t i = low - 1;

    for (int32_t j = low; j < high; j++)
    {
        comparisons_++;
        if (data[j] > pivot)
        {
            i++;
            if (i != j)
            {
                std::swap(data[i], data[j]);
                swaps_++;
            }
        }
    }

    if (i + 1 != high)
    {
        std::swap(data[i + 1], data[high]);
        swaps_++;
    }
    return i + 1;
}

void QuickSortAlgorithm::QuickSortRecursive(std::vector<int32_t>& data,
    const int32_t low, const int32_t high)
{
    if (low < high)
    {
        const int32_t pi = Partition(data, low, high);
        QuickSortRecursive(data, low, pi - 1);
        QuickSortRecursive(data, pi + 1, high);
    }
}

SortResult QuickSortAlgorithm::Sort(std::vector<int32_t>& data)
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
    QuickSortRecursive(data, 0, static_cast<int32_t>(data.size()) - 1);
    result.elapsed_ms = timer::ElapsedMs(start, timer::Now());
    result.comparisons = comparisons_;
    result.swaps = swaps_;
    return result;
}
