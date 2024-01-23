#include "board.hpp"

GameBoard::GameBoard(const std::size_t rows, const std::size_t cols)
    : rows(rows), cols(cols) {
    
    board.resize(rows);
    for (std::size_t i = 0; i < rows; i++)
        board[i].resize(i % 2 == 0 ? cols : cols - 1);
}

void GameBoard::update(const std::size_t row, const std::size_t col, const Bubble::Color color) {
    board[row][col].color = color;
}

bool GameBoard::compare(const std::size_t row, const std::size_t col, const int rowOffset, const int colOffset) const {
    if (row + rowOffset >= rows or col + colOffset >= cols or row + rowOffset < 0 or col + colOffset < 0)
        return false;

    return board[row][col].color == board[row + rowOffset][col + colOffset].color;
}

bool GameBoard::shouldPop(const std::size_t row, const std::size_t col) const {
    if (board[row][col].color == Bubble::Color::NONE or board[row][col].neighbors < MATCHES_TO_POP)
        return false;

    std::size_t matching = 0;
    matching += compare(row, col, 0, -1); 
    matching += compare(row, col, 0, 1);
    matching += compare(row, col, -1, 0);
    matching += compare(row, col, 1, 0);
    matching += compare(row, col, -1, row % 2 == 0 ? -1 : 1);
    matching += compare(row, col, 1, row % 2 == 0 ? -1 : 1);

    return matching >= MATCHES_TO_POP;
}
