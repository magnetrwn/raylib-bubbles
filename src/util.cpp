#include "util.hpp"

std::string GameUtils::getExecutablePath() {
    // NOTE: linux only, here is a comment from unistd.h on readlink():
    // "Read the contents of the symbolic link PATH into no more than LEN bytes of BUF. The contents are not null-terminated.
    //  Returns the number of characters read, or -1 for errors."

    char buffer[PATH_BUFFER_SIZE];
    ssize_t pathLength = readlink("/proc/self/exe", buffer, PATH_BUFFER_SIZE - 1);

    if (pathLength == -1)
        throw std::runtime_error("Error with GameUtils::getExecutablePath().");

    std::string path(buffer, pathLength);

    return path.substr(0, path.rfind('/') + 1);
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
