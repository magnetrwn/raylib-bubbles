#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <cstddef>
#include "board.hpp"

class GameUtils {
public:
    static bool clamp(float& value, const float lowLimit, const float highLimit);
    static bool usedLast(const size_t row, const size_t col);
};

#endif