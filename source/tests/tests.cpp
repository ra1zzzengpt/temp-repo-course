#include "tests.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cstdint>

#include "sort_algorithm/bubble_sort.h"
#include "sort_algorithm/selection_sort.h"
#include "sort_algorithm/insert_sort.h"
#include "sort_algorithm/shell_sort.h"
#include "sort_algorithm/quick_sort.h"
#include "utils/matrix_utils.h"
#include "models/matrix.h"

namespace
{
    int g_passed = 0;
    int g_failed = 0;

    void Check(const std::string& name,
               const std::vector<int32_t>& got,
               const std::vector<int32_t>& expected)
    {
        if (got == expected) { g_passed++; return; }
        g_failed++;
        std::cout << "[FAIL] " << name << "\n  Expected: ";
        for (const int32_t v : expected) std::cout << v << " ";
        std::cout << "\n  Got:      ";
        for (const int32_t v : got)      std::cout << v << " ";
        std::cout << "\n";
    }

    void CheckBool(const std::string& name, bool ok, const std::string& detail = "")
    {
        if (ok) { g_passed++; return; }
        g_failed++;
        std::cout << "[FAIL] " << name;
        if (!detail.empty()) std::cout << ": " << detail;
        std::cout << "\n";
    }

    void CheckMatrix(const std::string& name, const Matrix& got, const Matrix& expected)
    {
        if (got == expected) { g_passed++; return; }
        g_failed++;
        std::cout << "[FAIL] " << name << "\n  Expected:\n";
        for (const auto& row : expected)
        {
            std::cout << "    ";
            for (int32_t v : row) std::cout << v << " ";
            std::cout << "\n";
        }
        std::cout << "  Got:\n";
        for (const auto& row : got)
        {
            std::cout << "    ";
            for (int32_t v : row) std::cout << v << " ";
            std::cout << "\n";
        }
    }

    std::vector<int32_t> RunSort(ISort& algo, std::vector<int32_t> v)
    {
        algo.Sort(v);
        return v;
    }
}

namespace tests
{

bool RunAll()
{
    g_passed = 0;
    g_failed = 0;

    const std::vector<int32_t> input       = {3, 1, 4, 1, 5, 9, 2, 6};
    const std::vector<int32_t> sorted_desc = {9, 6, 5, 4, 3, 2, 1, 1};

    // --- Test 1: Bubble sort descending ---
    { BubbleSortAlgorithm    a; Check("Bubble: basic desc",    RunSort(a, input), sorted_desc); }
    // --- Test 2: Selection sort descending ---
    { SelectionSortAlgorithm a; Check("Selection: basic desc", RunSort(a, input), sorted_desc); }
    // --- Test 3: Insert sort descending ---
    { InsertSortAlgorithm    a; Check("Insert: basic desc",    RunSort(a, input), sorted_desc); }
    // --- Test 4: Shell sort descending ---
    { ShellSortAlgorithm     a; Check("Shell: basic desc",     RunSort(a, input), sorted_desc); }
    // --- Test 5: Quick sort descending ---
    { QuickSortAlgorithm     a; Check("Quick: basic desc",     RunSort(a, input), sorted_desc); }

    // --- Test 6: Empty vector → completed=false ---
    {
        std::vector<int32_t> empty;
        BubbleSortAlgorithm    b; SelectionSortAlgorithm s;
        InsertSortAlgorithm    i; ShellSortAlgorithm    sh;
        QuickSortAlgorithm     q;
        CheckBool("Empty: bubble",    !b.Sort(empty).completed);
        CheckBool("Empty: selection", !s.Sort(empty).completed);
        CheckBool("Empty: insert",    !i.Sort(empty).completed);
        CheckBool("Empty: shell",     !sh.Sort(empty).completed);
        CheckBool("Empty: quick",     !q.Sort(empty).completed);
    }

    // --- Test 7: Already sorted stays same ---
    {
        const std::vector<int32_t> already = {9, 7, 5, 3, 1};
        BubbleSortAlgorithm a;
        Check("Bubble: already sorted desc", RunSort(a, already), already);
    }

    // --- Test 8: Single element → unchanged ---
    {
        const std::vector<int32_t> single = {42};
        QuickSortAlgorithm a;
        Check("Quick: single element", RunSort(a, single), single);
    }

    // --- Test 9: Negative values ---
    {
        // [-2, 3, -4, 1, 2] sorted desc → [3, 2, 1, -2, -4]
        InsertSortAlgorithm a;
        Check("Insert: with negatives",
            RunSort(a, {-2, 3, -4, 1, 2}),
            {3, 2, 1, -2, -4});
    }

    // --- Test 10: Matrix even-column sort ---
    // Source: [[2,4],[6,1],[3,8]]
    // Col0: even at rows 0,1 → [2,6] → desc [6,2]
    // Col1: even at rows 0,2 → [4,8] → desc [8,4]
    // Expected: [[6,8],[2,1],[3,4]]
    {
        Matrix source   = {{2, 4}, {6, 1}, {3, 8}};
        Matrix expected = {{6, 8}, {2, 1}, {3, 4}};
        BubbleSortAlgorithm a;
        CheckMatrix("Matrix even-col sort", matrix_utils::SortEvenColumns(a, source).matrix, expected);
    }

    // --- Test 11: Matrix with all odd → unchanged ---
    {
        Matrix source = {{1, 3}, {5, 7}};
        BubbleSortAlgorithm a;
        CheckMatrix("Matrix all-odd: unchanged", matrix_utils::SortEvenColumns(a, source).matrix, source);
    }

    // --- Test 12: Comparisons counter > 0 ---
    {
        BubbleSortAlgorithm a;
        std::vector<int32_t> v = {5, 3, 1};
        const SortResult r = a.Sort(v);
        CheckBool("Comparisons counter > 0", r.comparisons > 0,
            "got " + std::to_string(r.comparisons));
    }

    if (g_failed == 0)
    {
        std::cout << "Testing successful ("
                  << g_passed << "/" << (g_passed + g_failed) << " passed)\n";
        return true;
    }
    std::cout << g_failed << " test(s) FAILED, " << g_passed << " passed.\n";
    return false;
}

} // namespace tests
