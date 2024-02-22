#include "util.hpp"

std::string GameUtils::getAbsDir() {
    // NOTE: linux only, here is a comment from unistd.h on readlink():
    // "Read the contents of the symbolic link PATH into no more than LEN bytes of BUF. The contents are not null-terminated.
    //  Returns the number of characters read, or -1 for errors."

    char buffer[PATH_BUFFER_SIZE];
    ssize_t pathLength = readlink("/proc/self/exe", buffer, PATH_BUFFER_SIZE - 1);

    if (pathLength == -1)
        throw std::runtime_error("Error with GameUtils::getAbsDir().");

    std::string path(buffer, pathLength);

    return path.substr(0, path.rfind('/') + 1);
}

std::string GameUtils::getCfgStr(const std::string& section, const std::string& key) {
    inipp::Ini<char> ini;
    std::ifstream is(getAbsDir() + CFG_RELATIVE_PATH); // TODO: this library could use some move constructors
    ini.parse(is);

    std::string value;
    inipp::get_value(ini.sections[section], key, value);

    return value;
}

size_t GameUtils::getCfgSizeT(const std::string& section, const std::string& key) {
    return static_cast<size_t>(std::stoi(getCfgStr(section, key)));
}

float GameUtils::getCfgFloat(const std::string& section, const std::string& key) {
    std::cout << section << ", " << key <<  ", " << getCfgStr(section, key) << std::endl;
    return std::stof(getCfgStr(section, key));
}

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

// TODO: all these could be constexpr if radius were constexpr!

int GameUtils::xyToCol(const float x, const float y, const float radius) {
    // NOTE: commented out underflow bounds check, it should be handled by the caller
    //const int col = ((x - (yToRow(y, radius) % 2 == 0 ? 0 : radius)) / (2 * radius));
    //return col < 0 ? 0 : static_cast<size_t>(col);
    
    return static_cast<int>(((x - (yToRow(y, radius) % 2 == 0 ? 0 : radius)) / (2 * radius)));
}

int GameUtils::yToRow(const float y, const float radius) {
    return static_cast<int>(y / (2 * radius));
}

float GameUtils::rowColToX(const size_t row, const size_t col, const float radius) {
    return static_cast<float>(col * 2) * radius + (row % 2 == 0 ? 0.0f : radius);
}

float GameUtils::rowToY(const size_t row, const float radius) {
    return static_cast<float>(row * 2) * radius;
}
