#include "files.h"

#include <fstream>
#include <iostream>
#include <iomanip>

std::string GetSafeWritePath(const std::string& suggested)
{
    namespace fs = std::filesystem;
    std::string path = suggested;

    while (true)
    {
        if (fs::exists(path))
        {
            const auto perms = fs::status(path).permissions();
            const bool writable = (perms & fs::perms::owner_write) != fs::perms::none;
            if (!writable)
            {
                std::cout << "[Error]: file is read-only: " << path << "\nEnter new path: ";
                std::getline(std::cin, path);
                continue;
            }
            std::cout << "File already exists: " << path << "\nOverwrite? (y/n): ";
            std::string choice;
            std::getline(std::cin, choice);
            if (!choice.empty() && (choice[0] == 'y' || choice[0] == 'Y'))
                return path;
            std::cout << "Enter new path: ";
            std::getline(std::cin, path);
            continue;
        }
        // Try to create the file
        {
            std::ofstream test(path);
            if (test.is_open()) { test.close(); fs::remove(path); return path; }
        }
        std::cout << "[Error]: cannot write to: " << path << "\nEnter new path: ";
        std::getline(std::cin, path);
    }
}

void WriteMatrixToFile(const std::string& path, const Matrix& m)
{
    const size_t rows = m.size();
    const size_t cols = rows > 0 ? m[0].size() : 0;
    std::ofstream f(path);
    if (!f.is_open()) { std::cout << "[Error]: cannot open " << path << "\n"; return; }

    f << rows << " " << cols << "\n";
    for (const auto& row : m)
    {
        for (size_t c = 0; c < row.size(); ++c)
        {
            if (c) f << " ";
            f << row[c];
        }
        f << "\n";
    }
    std::cout << "Matrix saved to: " << path << "\n";
}

bool ScanMatrixFromFile(const std::string& path, Matrix& m)
{
    std::ifstream f(path);
    if (!f.is_open()) { std::cout << "[Error]: cannot open " << path << "\n"; return false; }

    size_t rows = 0, cols = 0;
    if (!(f >> rows >> cols) || rows == 0 || cols == 0)
    {
        std::cout << "[Error]: invalid matrix header in " << path << "\n";
        return false;
    }
    m.assign(rows, std::vector<int32_t>(cols, 0));
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            if (!(f >> m[r][c]))
            {
                std::cout << "[Error]: not enough data in file\n";
                return false;
            }
    std::cout << "Matrix loaded from: " << path << "\n";
    return true;
}

void SaveResultsToFile(const std::string& path, const Matrix& source,
                       const std::vector<MatrixSortResult>& results)
{
    std::ofstream f(path);
    if (!f.is_open()) { std::cout << "[Error]: cannot open " << path << "\n"; return; }

    const size_t rows = source.size();
    const size_t cols = rows > 0 ? source[0].size() : 0;

    f << "===== SOURCE MATRIX (" << rows << "x" << cols << ") =====\n";
    for (const auto& row : source)
    {
        for (size_t c = 0; c < row.size(); ++c)
        {
            if (c) f << " ";
            f << std::setw(6) << row[c];
        }
        f << "\n";
    }
    f << "\n";

    for (const auto& msr : results)
    {
        f << "===== " << msr.stats.algorithm_name << " =====\n";
        for (const auto& row : msr.matrix)
        {
            for (size_t c = 0; c < row.size(); ++c)
            {
                if (c) f << " ";
                f << std::setw(6) << row[c];
            }
            f << "\n";
        }
        f << "  Comparisons: " << msr.stats.comparisons
          << "  Swaps: " << msr.stats.swaps
          << "  Time: " << msr.stats.elapsed_ms << " ms\n\n";
    }

    const int w = 16;
    f << "===== COMPARISON TABLE =====\n";
    f << std::left
      << std::setw(w) << "Algorithm"
      << std::setw(w) << "Comparisons"
      << std::setw(w) << "Swaps"
      << "Time (ms)\n";
    f << std::string(w * 3 + 10, '-') << "\n";
    for (const auto& msr : results)
        f << std::left
          << std::setw(w) << msr.stats.algorithm_name
          << std::setw(w) << msr.stats.comparisons
          << std::setw(w) << msr.stats.swaps
          << msr.stats.elapsed_ms << "\n";

    std::cout << "Results saved to: " << path << "\n";
}
