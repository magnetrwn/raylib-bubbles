#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <cstddef>
#include <string>
#include <fstream>
#include <stdexcept>

#include <unistd.h>

#include <inipp.h>

class GameUtils {
public:
    // NOTE: file I/O tools
    static std::string getAbsDir();
    static std::string getCfgStr(const std::string& section, const std::string& key);
    static size_t getCfgSizeT(const std::string& section, const std::string& key);
    static float getCfgFloat(const std::string& section, const std::string& key);

    static bool clamp(float& value, const float lowLimit, const float highLimit);

    // NOTE: hexagonal grid offset conversion tools
    static int xyToCol(const float x, const float y, const float radius);
    static int yToRow(const float y, const float radius);
    static float rowColToX(const size_t row, const size_t col, const float radius);
    static float rowToY(const size_t row, const float radius);
};

#endif