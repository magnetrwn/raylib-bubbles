#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>
#include <unordered_set>
#include <stdexcept>
#include <algorithm>

class GameBoard {
public:
    struct BubbleCell {
        size_t hue;
        size_t neighbors;

        // NOTE: Zero hue is empty space on the board, which is why the empty() method checks == 0.
        BubbleCell(size_t hue = 0, size_t neighbors = 0) : hue(hue), neighbors(neighbors) {}

        bool operator==(const BubbleCell& other) const {
            return hue == other.hue;
        }

        bool operator!=(const BubbleCell& other) const {
            return hue != other.hue;
        }

        void operator=(const size_t hue) {
            this->hue = hue;
        }
    };
    
    GameBoard(const size_t rows, const size_t cols) : rows(rows), cols(cols), board(hexGridSize(rows)) {};

    size_t getRows() const;
    size_t getCols() const;
    size_t hexAlign(const size_t row) const;
    size_t hexGridSize(const size_t nRows) const;

    size_t get(const size_t row, const size_t col) const;
    size_t getNbrs(const size_t row, const size_t col) const;
    void set(const size_t row, const size_t col, const size_t hue);

    size_t count() const;

    bool oob(const size_t row, const size_t col) const;
    bool canAttach(const size_t row, const size_t col) const;

    // NOTE: both of these return true on success
    bool attach(const size_t row, const size_t col, const size_t hue);
    bool pop(const size_t row, const size_t col, const size_t matches = MATCHES_TO_POP);

    void dropFloating();

    bool reachedBottom() const;

    // NOTE: attach + pop + dropFloating, return attach
    bool update(const size_t row, const size_t col, const size_t hue, const size_t matches = MATCHES_TO_POP);

    void clear();

protected: 
    static constexpr size_t MATCHES_TO_POP = 3;

    const size_t rows;
    const size_t cols;

    std::vector<BubbleCell> board;

    inline size_t at(const size_t row, const size_t col) const;
    inline void applyNbr(std::vector<BubbleCell>& b, const size_t srcRow, const size_t srcCol, const size_t dstRow, const size_t dstCol);

    bool compare(const size_t row, const size_t col, const int rowOffset, const int colOffset) const;
};

#endif