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

Color GameUtils::asRaylibColor(const int hue) {
    switch (hue) {
        case 0: return BLANK;
        case 1: return RED;
        case 2: return GREEN;
        case 3: return BLUE;
        case 4: return YELLOW;
        case 5: return ORANGE;
        case 6: return PURPLE;
        case 7: return PINK;
    }
    return BLANK;
}