#include "random.h"
#include <random>

int32_t GenerateRandom(const int32_t min, const int32_t max)
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution dist(min, max);
    return dist(gen);
}
