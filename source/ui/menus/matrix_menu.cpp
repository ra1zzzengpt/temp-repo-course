#include "matrix_menu.h"

#include <iostream>
#include <string>
#include <memory>
#include "ui/console.h"
#include "utils/files.h"
#include "utils/matrix_utils.h"
#include "utils/algorithm_factory.h"
#include "models/matrix.h"

namespace
{
    Matrix CreateMatrix()
    {
        while (true)
        {
            console::output::print("\n  Fill method:");
            console::output::print("  1. Random");
            console::output::print("  2. Keyboard");
            console::output::print("  3. From file");

            const uint32_t choice = console::input::SafeScanUint32_t("Enter choice: ");

            if (choice == static_cast<uint32_t>(MATRIX_CREATE::RANDOM))
            {
                const uint32_t rows = console::input::SafeScanUint32_t("Rows (N): ");
                const uint32_t cols = console::input::SafeScanUint32_t("Cols (M): ");
                if (rows == 0 || cols == 0)
                {
                    console::output::print("[Error]: dimensions must be > 0", console::COLOR::RED);
                    continue;
                }
                int32_t mn = 0, mx = 100;
                {
                    std::string s;
                    std::cout << "Min value: "; std::getline(std::cin, s);
                    try { mn = std::stoi(s); } catch (...) {}
                    std::cout << "Max value: "; std::getline(std::cin, s);
                    try { mx = std::stoi(s); } catch (...) {}
                }
                if (mn > mx) std::swap(mn, mx);
                return matrix_utils::FillRandom(rows, cols, mn, mx);
            }

            if (choice == static_cast<uint32_t>(MATRIX_CREATE::KEYBOARD))
            {
                const uint32_t rows = console::input::SafeScanUint32_t("Rows (N): ");
                const uint32_t cols = console::input::SafeScanUint32_t("Cols (M): ");
                if (rows == 0 || cols == 0)
                {
                    console::output::print("[Error]: dimensions must be > 0", console::COLOR::RED);
                    continue;
                }
                return matrix_utils::FillByKeyboard(rows, cols);
            }

            if (choice == static_cast<uint32_t>(MATRIX_CREATE::FROM_FILE))
            {
                std::string path;
                std::cout << "File path: ";
                std::getline(std::cin, path);
                Matrix m;
                if (ScanMatrixFromFile(path, m)) return m;
                continue;
            }

            console::output::print("[Error]: enter 1-3", console::COLOR::RED);
        }
    }
}

void MatrixMenu()
{
    console::clear();
    bool running = true;
    Matrix matrix;
    std::vector<MatrixSortResult> last_results;

    while (running)
    {
        console::output::print("\n╔══════════════════════════════╗");
        console::output::print("║     MATRIX OPERATIONS        ║");
        console::output::print("╠══════════════════════════════╣");
        console::output::print("║  1. Fill matrix               ║");
        console::output::print("║  2. Display matrix            ║");
        console::output::print("║  3. Sort                      ║");
        console::output::print("║  4. Save matrix to file       ║");
        console::output::print("║  5. Load matrix from file     ║");
        console::output::print("║  6. Save results to file      ║");
        console::output::print("║  7. Back                      ║");
        console::output::print("╚══════════════════════════════╝");

        switch (console::input::SafeScanUint32_t("Enter your choice: "))
        {
            case static_cast<uint32_t>(MATRIX_MENU::FILL):
            {
                console::clear();
                matrix = CreateMatrix();
                last_results.clear();
                console::clear();
                console::output::print("Matrix filled:", console::COLOR::GREEN);
                matrix_utils::PrintMatrix(matrix);
                break;
            }
            case static_cast<uint32_t>(MATRIX_MENU::PRINT):
            {
                console::clear();
                console::output::print("=== Matrix ===");
                matrix_utils::PrintMatrix(matrix);
                break;
            }
            case static_cast<uint32_t>(MATRIX_MENU::SORT):
            {
                console::clear();
                if (matrix.empty())
                {
                    console::output::print("[Error]: fill the matrix first", console::COLOR::RED);
                    break;
                }

                console::output::print("\n╔══════════════════════════════╗");
                console::output::print("║     SELECT ALGORITHM         ║");
                console::output::print("╠══════════════════════════════╣");
                console::output::print("║  1. All methods               ║");
                console::output::print("║  2. Bubble sort               ║");
                console::output::print("║  3. Selection sort            ║");
                console::output::print("║  4. Insert sort               ║");
                console::output::print("║  5. Shell sort                ║");
                console::output::print("║  6. Quick sort                ║");
                console::output::print("║  7. Back                      ║");
                console::output::print("╚══════════════════════════════╝");

                const uint32_t alg = console::input::SafeScanUint32_t("Enter your choice: ");
                if (alg == static_cast<uint32_t>(SORT_MENU::BACK)) break;

                console::clear();
                console::output::print("=== UNSORTED MATRIX ===");
                matrix_utils::PrintMatrix(matrix);

                if (alg == static_cast<uint32_t>(SORT_MENU::ALL))
                {
                    last_results = matrix_utils::RunAllSorts(matrix);
                    for (const auto& msr : last_results)
                    {
                        console::output::print("=== " + msr.stats.algorithm_name + " ===");
                        matrix_utils::PrintMatrix(msr.matrix);
                    }
                    matrix_utils::PrintComparisonTable(last_results);
                }
                else
                {
                    SortType type = SortType::BUBBLE;
                    switch (alg)
                    {
                        case static_cast<uint32_t>(SORT_MENU::BUBBLE):    type = SortType::BUBBLE;    break;
                        case static_cast<uint32_t>(SORT_MENU::SELECTION): type = SortType::SELECTION; break;
                        case static_cast<uint32_t>(SORT_MENU::INSERT):    type = SortType::INSERTION; break;
                        case static_cast<uint32_t>(SORT_MENU::SHELL):     type = SortType::SHELL;     break;
                        case static_cast<uint32_t>(SORT_MENU::QUICK):     type = SortType::QUICK;     break;
                        default:
                            console::output::print("[Error]: enter 1-7", console::COLOR::RED);
                            break;
                    }
                    std::unique_ptr<ISort> algo = CreateAlgorithm(type);
                    if (algo)
                    {
                        MatrixSortResult msr = matrix_utils::SortEvenColumns(*algo, matrix);
                        console::output::print("=== " + msr.stats.algorithm_name + " ===");
                        matrix_utils::PrintMatrix(msr.matrix);
                        console::output::print("Comparisons: " + std::to_string(msr.stats.comparisons)
                            + "  Swaps: " + std::to_string(msr.stats.swaps)
                            + "  Time: " + std::to_string(msr.stats.elapsed_ms) + " ms");
                        last_results = {msr};
                    }
                }
                break;
            }
            case static_cast<uint32_t>(MATRIX_MENU::SAVE_DATA):
            {
                console::clear();
                std::string path;
                std::cout << "Save path: ";
                std::getline(std::cin, path);
                path = GetSafeWritePath(path);
                WriteMatrixToFile(path, matrix);
                break;
            }
            case static_cast<uint32_t>(MATRIX_MENU::LOAD_DATA):
            {
                console::clear();
                std::string path;
                std::cout << "Load path: ";
                std::getline(std::cin, path);
                if (ScanMatrixFromFile(path, matrix))
                {
                    last_results.clear();
                    matrix_utils::PrintMatrix(matrix);
                }
                break;
            }
            case static_cast<uint32_t>(MATRIX_MENU::SAVE_RESULTS):
            {
                console::clear();
                if (last_results.empty())
                {
                    console::output::print("[Error]: run sort first (option 3)", console::COLOR::RED);
                    break;
                }
                std::string path;
                std::cout << "Save path: ";
                std::getline(std::cin, path);
                path = GetSafeWritePath(path);
                SaveResultsToFile(path, matrix, last_results);
                break;
            }
            case static_cast<uint32_t>(MATRIX_MENU::QUIT):
                running = false;
                console::clear();
                break;
            default:
                console::clear();
                console::output::print("[Error]: enter 1-7", console::COLOR::RED);
                break;
        }
    }
}
