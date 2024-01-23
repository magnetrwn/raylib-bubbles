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