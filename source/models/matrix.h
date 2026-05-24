#pragma once
#include <vector>
#include "sort_result.h"

using Matrix = std::vector<std::vector<int32_t>>;

struct MatrixSortResult
{
    SortResult stats;
    Matrix matrix;
};
