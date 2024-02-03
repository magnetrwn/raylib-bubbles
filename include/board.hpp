#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <new>
#include <stdexcept>

class GameBoard {
public:
    struct Bubble {
        int hue;
        int neighbors;

        Bubble(int hue = 0, int neighbors = 0) : hue(hue), neighbors(neighbors) {}

        bool operator==(const Bubble& other) const {
            return hue == other.hue;
        }

        void operator=(const int hue) {
            this->hue = hue;
        }

        bool empty() const {
            return hue == 0;
        }
    };
    
    GameBoard(const int rows = DEFAULT_ROWS, const int cols = DEFAULT_COLS);
    ~GameBoard();

    int getRows() const;
    int getCols() const;

    int get(const int row, const int col) const;
    void set(const int row, const int col, const int hue);

    bool shouldPop(const int row, const int col) const;
    bool shouldDrop(const int row, const int col) const;

protected: 
    static constexpr int DEFAULT_ROWS = 8;
    static constexpr int DEFAULT_COLS = 10;

    static constexpr int MATCHES_TO_POP = 2;

    int rows; // TODO: using int everywhere for now, but should be size_t for best practice
    int cols;

    Bubble* board;

    inline int hexAlign(const int row) const;
    inline int hexGridSize(const int nRows = DEFAULT_ROWS) const;
    inline bool oob(const int row, const int col) const;
    inline int at(const int row, const int col) const;
    inline void applyNbr(const int srcRow, const int srcCol, const int dstRow, const int dstCol);

    bool compare(const int row, const int col, const int rowOffset, const int colOffset) const;
};

#endif