#pragma once

#include <memory>
#include <vector>
#include "interfaces/i_sort_algorithm.h"

enum class SortType { BUBBLE=1, INSERTION=2, SELECTION=3, SHELL=4, QUICK=5 };

inline const std::vector algorithm_names = {
    SortType::BUBBLE, SortType::INSERTION, SortType::SELECTION,
    SortType::SHELL,  SortType::QUICK
};

std::unique_ptr<ISort> CreateAlgorithm(SortType sort_type);
