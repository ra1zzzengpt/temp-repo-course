#include "algorithm_factory.h"

#include "sort_algorithm/bubble_sort.h"
#include "sort_algorithm/insert_sort.h"
#include "sort_algorithm/selection_sort.h"
#include "sort_algorithm/shell_sort.h"
#include "sort_algorithm/quick_sort.h"

std::unique_ptr<ISort> CreateAlgorithm(const SortType sort_type)
{
    if (sort_type == SortType::BUBBLE)    return std::make_unique<BubbleSortAlgorithm>();
    if (sort_type == SortType::INSERTION) return std::make_unique<InsertSortAlgorithm>();
    if (sort_type == SortType::SELECTION) return std::make_unique<SelectionSortAlgorithm>();
    if (sort_type == SortType::SHELL)     return std::make_unique<ShellSortAlgorithm>();
    if (sort_type == SortType::QUICK)     return std::make_unique<QuickSortAlgorithm>();
    return nullptr;
}
