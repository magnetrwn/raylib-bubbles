#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <cstddef>
#include "board.hpp"

class GameUtils {
public:
    static bool clamp(float& value, const float lowLimit, const float highLimit);
    static bool usedLast(const size_t row, const size_t col);

    // NOTE: hexagonal grid offset conversion tools
    static size_t xyToCol(const float x, const float y, const float radius);
    static size_t yToRow(const float y, const float radius);
    static float rowColToX(const size_t row, const size_t col, const float radius);
    static float rowToY(const size_t row, const float radius);
};

#endif