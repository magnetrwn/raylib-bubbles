#include "board.hpp"

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

size_t GameBoard::hexGridSize(const size_t nRows) const {
    return (nRows * hexAlign(0) + nRows * hexAlign(1) + 1) / 2;
}

size_t GameBoard::get(const size_t row, const size_t col) const {
    return board[at(row, col)].hue;
}

void GameBoard::set(const size_t row, const size_t col, const size_t hue) {
    if (board[at(row, col)] == hue)
        return;

    board[at(row, col)] = hue;
}

bool GameBoard::pop(const size_t row, const size_t col, const size_t matches) {
    if (board[at(row, col)].empty())
        return false;

    const size_t matchHue = board[at(row, col)].hue;

    std::vector<std::pair<size_t, size_t>> dfs, found;

    dfs.push_back({row, col});
    while (!dfs.empty()) {
        const std::pair<size_t, size_t> el = dfs.back();
        dfs.pop_back();

        if (oob(el.first, el.second) or board[at(el.first, el.second)].hue != matchHue)
            continue;

        found.push_back(el);

        dfs.push_back({ el.first, el.second - 1 });
        dfs.push_back({ el.first, el.second + 1 });
        dfs.push_back({ el.first - 1, el.second });
        dfs.push_back({ el.first + 1, el.second });
        dfs.push_back({ el.first - 1, el.second + (el.first % 2 == 0 ? -1 : 1) });
        dfs.push_back({ el.first + 1, el.second + (el.first % 2 == 0 ? -1 : 1) });

        set(el.first, el.second, 0);
    }

    if (found.size() >= matches)
        return true;
    
    for (const std::pair<size_t, size_t>& el : found)
        set(el.first, el.second, matchHue);

    // TODO: awkward, maybe better to use a set to track visited instead of switching bubbles to/from 0.

    return false;
}

bool GameBoard::setThenPop(const size_t row, const size_t col, const size_t hue, const size_t matches) {
    set(row, col, hue);
    return pop(row, col, matches);
}

/* --- protected --- */

bool GameBoard::oob(const size_t row, const size_t col) const {
    return row >= rows or col >= hexAlign(row);
}

size_t GameBoard::at(const size_t row, const size_t col) const {
    if (oob(row, col))
        throw std::out_of_range("Requested GameBoard::at(" + std::to_string(row) + ", " + std::to_string(col) + ") position is out of bounds.");

    return hexGridSize(row) + col;
}

bool GameBoard::compare(const size_t row, const size_t col, const int rowOffset, const int colOffset) const {
    return board[at(row, col)] == board[at(row + rowOffset, col + colOffset)];
}