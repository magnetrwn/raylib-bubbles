#ifndef UTIL_HPP_
#define UTIL_HPP_

#include "board.hpp"

class GameUtils {
public:
    static bool clamp(float& value, const float lowLimit, const float highLimit);
};

#endif