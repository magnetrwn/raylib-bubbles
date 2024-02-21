#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <cstddef>
#include "board.hpp"

class GameUtils {
public:
    static bool clamp(float& value, const float lowLimit, const float highLimit);

    // NOTE: hexagonal grid offset conversion tools
    static int xyToCol(const float x, const float y, const float radius);
    static int yToRow(const float y, const float radius);
    static float rowColToX(const size_t row, const size_t col, const float radius);
    static float rowToY(const size_t row, const float radius);
};

#endif