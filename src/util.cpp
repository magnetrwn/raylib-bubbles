#include "util.hpp"

bool GameUtils::clamp(float& value, const float lowLimit, const float highLimit) {
    if (value < lowLimit) {
        value = lowLimit;
        return true;
    }

    if (value > highLimit) {
        value = highLimit;
        return true;
    }

    return false;
}
