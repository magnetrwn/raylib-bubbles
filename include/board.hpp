#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>
#include <unordered_set>
#include <array>
#include <stdexcept>
#include <algorithm>

#include "util.hpp"

class GameBoard {
public:
    struct BubbleCell {
        size_t hue;
        size_t neighbors;

        // NOTE: Zero hue is empty space on the board, which is why the empty() method checks == 0.
        BubbleCell(size_t hue = 0, size_t neighbors = 0) 
            : hue(hue), neighbors(neighbors) {}

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
    
    GameBoard(const size_t rows, const size_t cols) 
        : rows(rows), cols(cols), matchesToPop(GameUtils::getCfgSizeT("Game.Board", "MATCHES_TO_POP")), board(getGridSize(rows)) {};

    size_t getRows() const;
    size_t getCols() const;
    size_t getColAlign(const size_t row) const;
    size_t getGridSize(const size_t nRows) const;

    size_t get(const size_t row, const size_t col) const;
    size_t getNbrs(const size_t row, const size_t col) const;
    void set(const size_t row, const size_t col, const size_t hue);

    size_t count() const;

    bool oob(const size_t row, const size_t col) const;
    bool canAttach(const size_t row, const size_t col) const;

    // NOTE: both of these return true on success
    bool attach(const size_t row, const size_t col, const size_t hue);
    bool pop(const size_t row, const size_t col, const size_t matches = 0);

    void dropFloating();

    bool reachedBottom() const;

    // NOTE: attach + pop + dropFloating, return attach
    bool update(const size_t row, const size_t col, const size_t hue, const size_t matches = 0);

    void clear();

protected:
    const size_t rows;
    const size_t cols;

    // NOTE: default matches to pop, which gets used if matches is the default (0) for pop()
    const size_t matchesToPop;

    std::vector<BubbleCell> board;

    size_t at(const size_t row, const size_t col) const;
    void applyNbrs(std::vector<BubbleCell>& b, const size_t row, const size_t col);

    std::array<std::pair<int, int>, 6> getOffsets(const size_t row) const;
};

#endif