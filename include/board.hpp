#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <cstddef>
#include <vector>

class GameBoard {
protected: 
    static constexpr std::size_t MATCHES_TO_POP = 2;

    struct Bubble {
        enum class Color { NONE, RED, YELLOW, BLUE };

        Color color;
        std::size_t neighbors;

        Bubble(Color color = Color::NONE, std::size_t neighbors = 0) : color(color), neighbors(neighbors) {}
    };

    std::size_t rows;
    std::size_t cols;

    std::vector<std::vector<Bubble>> board;

public:
    GameBoard(const std::size_t rows = 8, const std::size_t cols = 10);

    void update(const std::size_t row, const std::size_t col, const Bubble::Color color);

    bool compare(const std::size_t row, const std::size_t col, const int rowOffset, const int colOffset) const;
    bool shouldPop(const std::size_t row, const std::size_t col) const;
    bool shouldDrop(const std::size_t row, const std::size_t col) const;
};

#endif