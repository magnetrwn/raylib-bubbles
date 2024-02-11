#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <new>
#include <stdexcept>

class GameBoard {
public:
    struct Bubble {
        size_t hue;
        size_t neighbors;

        // NOTE: Zero hue is empty space on the board, which is why the empty() method checks == 0.
        Bubble(size_t hue = 0, size_t neighbors = 0) : hue(hue), neighbors(neighbors) {}

        bool operator==(const Bubble& other) const {
            return hue == other.hue;
        }

        void operator=(const size_t hue) {
            this->hue = hue;
        }

        bool empty() const {
            return hue == 0;
        }
    };
    
    GameBoard(const size_t rows, const size_t cols);
    ~GameBoard();

    size_t getRows() const;
    size_t getCols() const;

    size_t get(const size_t row, const size_t col) const;
    void set(const size_t row, const size_t col, const size_t hue);

    size_t hexAlign(const size_t row) const;

    bool shouldPop(const size_t row, const size_t col) const;


protected: 
    static constexpr size_t MATCHES_TO_POP = 2;

    size_t rows;
    size_t cols;

    Bubble* board;

    inline size_t hexGridSize(const size_t nRows) const;
    inline bool oob(const size_t row, const size_t col) const;
    inline size_t at(const size_t row, const size_t col) const;

    inline void applyNbr(const size_t srcRow, const size_t srcCol, const size_t dstRow, const size_t dstCol);

    bool compare(const size_t row, const size_t col, const int rowOffset, const int colOffset) const;
};

#endif