#include "board.hpp"

/* --- initialization --- */

GameBoard::GameBoard(const size_t rows, const size_t cols)
    : rows(rows), cols(cols) {
    
    board = new Bubble[hexGridSize(rows)];
    for (size_t i = 0; i < hexGridSize(rows); i++)
        board[i] = Bubble();
}

GameBoard::~GameBoard() {
    delete[] board;
}

/* --- public --- */

size_t GameBoard::getRows() const {
    return rows;
}

size_t GameBoard::getCols() const {
    return cols;
}

size_t GameBoard::hexAlign(const size_t row) const {
    return row % 2 == 0 ? cols : cols - (cols % 2 == 0 ? 1 : 0);
}

size_t GameBoard::get(const size_t row, const size_t col) const {
    return board[at(row, col)].hue;
}

void GameBoard::set(const size_t row, const size_t col, const size_t hue) {
    if (board[at(row, col)] == hue)
        return;

    board[at(row, col)] = hue;

    applyNbr(row, col, row, col - 1);
    applyNbr(row, col, row, col + 1);
    applyNbr(row, col, row - 1, col);
    applyNbr(row, col, row + 1, col);
    applyNbr(row, col, row - 1, col + (row % 2 == 0 ? -1 : 1));
    applyNbr(row, col, row + 1, col + (row % 2 == 0 ? -1 : 1));
}

bool GameBoard::shouldPop(const size_t row, const size_t col) const {
    if (board[at(row, col)].empty() or board[at(row, col)].neighbors < MATCHES_TO_POP)
        return false;

    size_t matching = 0;

    matching += compare(row, col, 0, -1); 
    matching += compare(row, col, 0, 1);
    matching += compare(row, col, -1, 0);
    matching += compare(row, col, 1, 0);
    matching += compare(row, col, -1, row % 2 == 0 ? -1 : 1);
    matching += compare(row, col, 1, row % 2 == 0 ? -1 : 1);

    return matching >= MATCHES_TO_POP;
}

/* --- protected --- */

size_t GameBoard::hexGridSize(const size_t nRows) const {
    return (nRows * hexAlign(0) + nRows * hexAlign(1) + 1) / 2;
}

bool GameBoard::oob(const size_t row, const size_t col) const {
    // TODO: you can use size_t and only do the first two comparisons
    return row >= rows or col >= hexAlign(row);
}

size_t GameBoard::at(const size_t row, const size_t col) const {
    if (oob(row, col))
        throw std::out_of_range("Requested GameBoard::at(" + std::to_string(row) + ", " + std::to_string(col) + ") position is out of bounds.");

    return hexGridSize(row) + col;
}

void GameBoard::applyNbr(const size_t srcRow, const size_t srcCol, const size_t dstRow, const size_t dstCol) {
    // TODO: Do not run multiple times on the same hue
    if (oob(dstRow, dstCol) or oob(srcRow, srcCol))
        return;

    board[at(dstRow, dstCol)].neighbors += board[at(srcRow, srcCol)].empty() ? -1 : 1;
}

bool GameBoard::compare(const size_t row, const size_t col, const int rowOffset, const int colOffset) const {
    return board[at(row, col)] == board[at(row + rowOffset, col + colOffset)];
}