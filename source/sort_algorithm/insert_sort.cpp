#include "insert_sort.h"
#include "utils/timer.h"
std::string InsertSortAlgorithm::GetName() const { return "Insert sort"; }

SortResult InsertSortAlgorithm::Sort(std::vector<int32_t>& data)
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

    for (size_t i = 1; i < data.size(); i++)
    {
        const int32_t key = data[i];
        int32_t j = static_cast<int32_t>(i) - 1;
        while (j >= 0)
        {
            comparisons_++;
            if (key > data[j])
            {
                data[j + 1] = data[j];
                swaps_++;
                j--;
            }
            else break;
        }
        data[j + 1] = key;
    }

    result.elapsed_ms = timer::ElapsedMs(start, timer::Now());
    result.comparisons = comparisons_;
    result.swaps = swaps_;
    return result;
}
