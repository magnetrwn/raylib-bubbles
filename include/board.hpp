#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>

class GameBoard {
protected: 
    static constexpr int DEFAULT_ROWS = 8;
    static constexpr int DEFAULT_COLS = 10;

    static constexpr int MATCHES_TO_POP = 2;

    struct Bubble {
        enum class Color { NONE, RED, YELLOW, BLUE };

        Color color;
        int neighbors;

        Bubble(Color color = Color::NONE, int neighbors = 0) : color(color), neighbors(neighbors) {}

        bool operator==(const Bubble& other) const {
            return color == other.color;
        }

        void operator=(const Color color) {
            this->color = color;
        }

        bool isColorNone() const {
            return color == Color::NONE;
        }
    };

    int rows;
    int cols;

    std::vector<std::vector<Bubble>> board;

    bool oob(const int row, const int col) const;

    void setNbrsBounded(const int srcRow, const int srcCol, const int dstRow, const int dstCol);

public:
    GameBoard(const int rows = DEFAULT_ROWS, const int cols = DEFAULT_COLS);

    bool compare(const int row, const int col, const int rowOffset, const int colOffset) const;
    bool shouldPop(const int row, const int col) const;
    //bool shouldDrop(const int row, const int col) const;

    void update(const int row, const int col, const Bubble::Color color);
};

#endif