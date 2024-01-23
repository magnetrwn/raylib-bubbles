#include "board.hpp"

GameBoard::GameBoard(const int rows, const int cols)
    : rows(rows), cols(cols) {
    
    board.resize(rows);
    for (int i = 0; i < rows; i++)
        board[i].resize(i % 2 == 0 ? cols : cols - 1);
}

bool GameBoard::oob(const int row, const int col) const {
    return row < rows and col < (row % 2 == 0 ? cols : cols - 1) and row >= 0 and col >= 0;
}

bool GameBoard::compare(const int row, const int col, const int rowOffset, const int colOffset) const {
    if (oob(row, col) or oob(row + rowOffset, col + colOffset))
        return false;

    return board[row][col] == board[row + rowOffset][col + colOffset];
}

bool GameBoard::shouldPop(const int row, const int col) const {
    if (board[row][col].isColorNone() or board[row][col].neighbors < MATCHES_TO_POP)
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

void GameBoard::setNbrsBounded(const int srcRow, const int srcCol, const int dstRow, const int dstCol) {
    // TODO: Do not run multiple times on the same color
    if (oob(srcRow, srcCol) or oob(dstRow, dstCol))
        return;

    board[dstRow][dstCol].neighbors += board[srcRow][srcCol].isColorNone() ? -1 : 1;
}

void GameBoard::update(const int row, const int col, const Bubble::Color color) {
    if (board[row][col] == color)
        return;

    board[row][col] = color;

    setNbrsBounded(row, col, row, col - 1);
    setNbrsBounded(row, col, row, col + 1);
    setNbrsBounded(row, col, row - 1, col);
    setNbrsBounded(row, col, row + 1, col);
    setNbrsBounded(row, col, row - 1, col + (row % 2 == 0 ? -1 : 1));
    setNbrsBounded(row, col, row + 1, col + (row % 2 == 0 ? -1 : 1));
}