#ifndef UTIL_HPP_
#define UTIL_HPP_

#include "board.hpp"
#include <raylib.h>

class GameUtils {
public:
    static bool clamp(float& value, const float lowLimit, const float highLimit);
    static Color asRaylibColor(const int hue);
};

#endif