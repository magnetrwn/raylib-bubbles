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

size_t GameUtils::xyToCol(const float x, const float y, const float radius) {
    return static_cast<size_t>((x - (yToRow(y, radius) % 2 == 0 ? 0 : radius)) / (2 * radius));
}

size_t GameUtils::yToRow(const float y, const float radius) {
    return static_cast<size_t>(y / (2 * radius));
}

float GameUtils::rowColToX(const size_t row, const size_t col, const float radius) {
    return static_cast<float>(col * 2) * radius + (row % 2 == 0 ? 0.0f : radius);
}

float GameUtils::rowToY(const size_t row, const float radius) {
    return static_cast<float>(row * 2) * radius;
}
