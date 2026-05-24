#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "models/matrix.h"

// Returns a safe writable path: prompts user to overwrite or enter a new path.
std::string GetSafeWritePath(const std::string& suggested);

// Matrix file I/O — format: first line "N M", then N rows of M ints.
void WriteMatrixToFile(const std::string& path, const Matrix& m);
bool ScanMatrixFromFile(const std::string& path, Matrix& m);

// Saves full results (source matrix + sorted matrices + comparison table).
void SaveResultsToFile(const std::string& path, const Matrix& source,
                       const std::vector<MatrixSortResult>& results);
