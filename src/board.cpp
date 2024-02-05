#include "board.hpp"

/* --- initialization --- */

GameBoard::GameBoard(const int rows, const int cols)
    : rows(rows), cols(cols) {
    
    board = new Bubble[hexGridSize(rows)];
    for (int i = 0; i < hexGridSize(rows); i++)
        board[i] = Bubble();
}

GameBoard::~GameBoard() {
    delete[] board;
}

/* --- public --- */

int GameBoard::getRows() const {
    return rows;
}

int GameBoard::getCols() const {
    return cols;
}

int GameBoard::hexAlign(const int row) const {
    return row % 2 == 0 ? cols : cols - (cols % 2 == 0 ? 1 : 0);
}

int GameBoard::get(const int row, const int col) const {
    return board[at(row, col)].hue;
}

void GameBoard::set(const int row, const int col, const int hue) {
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

bool GameBoard::shouldPop(const int row, const int col) const {
    if (board[at(row, col)].empty() or board[at(row, col)].neighbors < MATCHES_TO_POP)
        return false;

    int matching = 0;

    matching += compare(row, col, 0, -1); 
    matching += compare(row, col, 0, 1);
    matching += compare(row, col, -1, 0);
    matching += compare(row, col, 1, 0);
    matching += compare(row, col, -1, row % 2 == 0 ? -1 : 1);
    matching += compare(row, col, 1, row % 2 == 0 ? -1 : 1);

    return matching >= MATCHES_TO_POP;
}

/*bool GameBoard::shouldDrop(const int row, const int col) const {

}*/

/* --- protected --- */

int GameBoard::hexGridSize(const int nRows) const {
    return (nRows * hexAlign(0) + nRows * hexAlign(1) + 1) / 2;
}

bool GameBoard::oob(const int row, const int col) const {
    // TODO: you can use size_t and only do the first two comparisons
    return row >= rows or col >= hexAlign(row) or row < 0 or col < 0;
}

int GameBoard::at(const int row, const int col) const {
    if (oob(row, col))
        throw std::out_of_range("Requested GameBoard::at(" + std::to_string(row) + ", " + std::to_string(col) + ") position is out of bounds.");

    return hexGridSize(row) + col;
}

void GameBoard::applyNbr(const int srcRow, const int srcCol, const int dstRow, const int dstCol) {
    // TODO: Do not run multiple times on the same hue
    if (oob(dstRow, dstCol) or oob(srcRow, srcCol))
        return;

    board[at(dstRow, dstCol)].neighbors += board[at(srcRow, srcCol)].empty() ? -1 : 1;
}

bool GameBoard::compare(const int row, const int col, const int rowOffset, const int colOffset) const {
    return board[at(row, col)] == board[at(row + rowOffset, col + colOffset)];
}