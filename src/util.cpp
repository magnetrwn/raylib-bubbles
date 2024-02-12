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

bool GameUtils::usedLast(const size_t row, const size_t col) {
    static size_t lastRow;
    static size_t lastCol;
    static bool first = true;

    if (!first and lastRow == row and lastCol == col) {
        first = false;
        return true;
    }

    lastRow = row;
    lastCol = col;

    return false;
}