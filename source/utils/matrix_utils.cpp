#include "matrix_utils.h"

#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include "utils/algorithm_factory.h"
#include "timer.h"

namespace matrix_utils
{

void PrintMatrix(const Matrix& m)
{
    if (m.empty()) { std::cout << "  [empty]\n"; return; }
    for (const auto& row : m)
    {
        std::cout << " ";
        for (size_t c = 0; c < row.size(); ++c)
        {
            std::cout << std::setw(6) << row[c];
            if (c + 1 < row.size()) std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix FillRandom(const size_t rows, const size_t cols, const int32_t min_val, const int32_t max_val)
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution dist(min_val, max_val);
    Matrix m(rows, std::vector<int32_t>(cols));
    for (auto& row : m)
        for (auto& cell : row)
            cell = dist(gen);
    return m;
}

Matrix FillByKeyboard(const size_t rows, const size_t cols)
{
    Matrix m(rows, std::vector<int32_t>(cols));
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
        {
            std::string input;
            std::cout << "  m[" << r << "][" << c << "] = ";
            while (true)
            {
                std::getline(std::cin, input);
                try { m[r][c] = std::stoi(input); break; }
                catch (...) { std::cout << "  [Error]: enter an integer: "; }
            }
        }
    return m;
}

MatrixSortResult SortEvenColumns(ISort& algo, const Matrix& source)
{
    MatrixSortResult msr;
    msr.matrix = source;
    msr.stats.algorithm_name = algo.GetName();

    if (source.empty() || source[0].empty())
    {
        msr.stats.completed = false;
        msr.stats.message = "Matrix is empty";
        return msr;
    }

    const size_t rows = source.size();
    const size_t cols = source[0].size();
    uint64_t total_comp = 0, total_swaps = 0;
    const auto t_start = timer::Now();

    for (size_t col = 0; col < cols; ++col)
    {
        std::vector<size_t>  even_pos;
        std::vector<int32_t> even_vals;

        for (size_t row = 0; row < rows; ++row)
        {
            if (msr.matrix[row][col] % 2 == 0)
            {
                even_pos.push_back(row);
                even_vals.push_back(msr.matrix[row][col]);
            }
        }
        if (even_vals.size() < 2) continue;

        const SortResult col_result = algo.Sort(even_vals);
        total_comp  += col_result.comparisons;
        total_swaps += col_result.swaps;

        for (size_t k = 0; k < even_pos.size(); ++k)
            msr.matrix[even_pos[k]][col] = even_vals[k];
    }

    msr.stats.comparisons = total_comp;
    msr.stats.swaps       = total_swaps;
    msr.stats.elapsed_ms  = timer::ElapsedMs(t_start, timer::Now());
    msr.stats.completed   = true;
    return msr;
}

std::vector<MatrixSortResult> RunAllSorts(const Matrix& source)
{
    std::vector<MatrixSortResult> results;
    results.reserve(algorithm_names.size());
    for (const SortType type : algorithm_names)
    {
        std::unique_ptr<ISort> algo = CreateAlgorithm(type);
        if (algo) results.push_back(SortEvenColumns(*algo, source));
    }
    return results;
}

void PrintComparisonTable(const std::vector<MatrixSortResult>& results)
{
    if (results.empty()) return;
    const int w = 16;
    std::cout << "\n===== COMPARISON TABLE =====\n";
    std::cout << std::left
              << std::setw(w) << "Algorithm"
              << std::setw(w) << "Comparisons"
              << std::setw(w) << "Swaps"
              << "Time (ms)\n";
    std::cout << std::string(w * 3 + 10, '-') << "\n";
    for (const auto& r : results)
        std::cout << std::left
                  << std::setw(w) << r.stats.algorithm_name
                  << std::setw(w) << r.stats.comparisons
                  << std::setw(w) << r.stats.swaps
                  << r.stats.elapsed_ms << "\n";
    std::cout << "\n";
}

} // namespace matrix_utils
