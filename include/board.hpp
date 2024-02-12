#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>
#include <stdexcept>

class GameBoard {
public:
    struct Bubble {
        size_t hue;

        // NOTE: Zero hue is empty space on the board, which is why the empty() method checks == 0.
        Bubble(size_t hue = 0) : hue(hue) {}

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
    
    GameBoard(const size_t rows, const size_t cols) : rows(rows), cols(cols), board(hexGridSize(rows)) {};

    size_t getRows() const;
    size_t getCols() const;
    size_t hexAlign(const size_t row) const;
    size_t hexGridSize(const size_t nRows) const;

    size_t get(const size_t row, const size_t col) const;
    void set(const size_t row, const size_t col, const size_t hue);
    bool pop(const size_t row, const size_t col, const size_t matches = MATCHES_TO_POP);
    bool setThenPop(const size_t row, const size_t col, const size_t hue, const size_t matches = MATCHES_TO_POP);

protected: 
    static constexpr size_t MATCHES_TO_POP = 3;

    size_t rows;
    size_t cols;

    std::vector<Bubble> board;

    inline bool oob(const size_t row, const size_t col) const;
    inline size_t at(const size_t row, const size_t col) const;

    bool compare(const size_t row, const size_t col, const int rowOffset, const int colOffset) const;
};

#endif