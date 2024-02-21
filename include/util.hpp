#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <cstddef>
#include <string>
#include <stdexcept>

#include <unistd.h>

#include "board.hpp"

class GameUtils {
public:
    // TODO: preprocessor directive to pick this if the platform is linux
    static std::string getExecutablePath();

    static bool clamp(float& value, const float lowLimit, const float highLimit);

    // NOTE: hexagonal grid offset conversion tools
    static int xyToCol(const float x, const float y, const float radius);
    static int yToRow(const float y, const float radius);
    static float rowColToX(const size_t row, const size_t col, const float radius);
    static float rowToY(const size_t row, const float radius);

protected:
    static constexpr size_t PATH_BUFFER_SIZE = 256;
};

#endif