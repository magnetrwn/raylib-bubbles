#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <new>
#include <stdexcept>

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

        bool empty() const {
            return color == Color::NONE;
        }
    };

    int rows; // TODO: using int everywhere for now, but should be size_t for best practice
    int cols;

    Bubble* board;

    inline int hexAlign(const int row) const;
    inline int hexGridSize(const int nRows = DEFAULT_ROWS) const;
    inline bool oob(const int row, const int col) const;
    inline int at(const int row, const int col) const;
    inline void applyNbr(const int srcRow, const int srcCol, const int dstRow, const int dstCol);

    bool compare(const int row, const int col, const int rowOffset, const int colOffset) const;

public:
    GameBoard(const int rows = DEFAULT_ROWS, const int cols = DEFAULT_COLS);
    ~GameBoard();

    Bubble::Color get(const int row, const int col) const;
    void set(const int row, const int col, const Bubble::Color color);

    bool shouldPop(const int row, const int col) const;
    bool shouldDrop(const int row, const int col) const;
};

#endif