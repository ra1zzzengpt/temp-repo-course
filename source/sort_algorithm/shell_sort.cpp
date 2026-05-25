#include "shell_sort.h"
#include "utils/timer.h"

std::string ShellSortAlgorithm::GetName() const { return "Shell sort"; }

SortResult ShellSortAlgorithm::Sort(std::vector<int32_t>& data)
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

    for (int32_t gap = static_cast<int32_t>(data.size()) / 2; gap > 0; gap /= 2)
    {
        for (int32_t i = gap; i < static_cast<int32_t>(data.size()); ++i)
        {
            const int32_t temp = data[i];
            int32_t j = i;
            while (j >= gap)
            {
                comparisons_++;
                if (data[j - gap] < temp)
                {
                    data[j] = data[j - gap];
                    swaps_++;
                    j -= gap;
                }
                else break;
            }
            data[j] = temp;
        }
    }

    result.elapsed_ms = timer::ElapsedMs(start, timer::Now());
    result.comparisons = comparisons_;
    result.swaps = swaps_;
    return result;
}
