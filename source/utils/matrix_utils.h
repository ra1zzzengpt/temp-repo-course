#pragma once

#include <vector>
#include "models/matrix.h"
#include "interfaces/i_sort_algorithm.h"

namespace matrix_utils
{
    void PrintMatrix(const Matrix& m);

    Matrix FillRandom(size_t rows, size_t cols, int32_t min_val, int32_t max_val);
    Matrix FillByKeyboard(size_t rows, size_t cols);

    MatrixSortResult SortEvenColumns(ISort& algo, const Matrix& source);

    std::vector<MatrixSortResult> RunAllSorts(const Matrix& source);

    void PrintComparisonTable(const std::vector<MatrixSortResult>& results);
}
