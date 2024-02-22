#include "board.hpp"

/* --- public --- */

size_t GameBoard::getRows() const {
    return rows;
}

size_t GameBoard::getCols() const {
    return cols;
}

size_t GameBoard::getColAlign(const size_t row) const {
    return row % 2 == 0 ? cols : cols - (cols % 2 == 0 ? 1 : 0);
}

size_t GameBoard::getGridSize(const size_t nRows) const {
    return (nRows * cols + nRows * getColAlign(1) + 1) / 2;
}

size_t GameBoard::get(const size_t row, const size_t col) const {
    return board[at(row, col)].hue;
}

size_t GameBoard::getNbrs(const size_t row, const size_t col) const {
    return board[at(row, col)].neighbors;
}

void GameBoard::set(const size_t row, const size_t col, const size_t hue) {
    if (board[at(row, col)] == hue)
        return;

    board[at(row, col)] = hue;

    applyNbrs(board, row, col);
}

size_t GameBoard::count() const {
    return std::count_if(board.begin(), board.end(), [] (const BubbleCell& cell) {
        return cell.hue != 0;
    });
}

bool GameBoard::oob(const size_t row, const size_t col) const {
    return row >= rows or col >= getColAlign(row);
}

bool GameBoard::canAttach(const size_t row, const size_t col) const {
    return board[at(row, col)] == 0 and (board[at(row, col)].neighbors != 0 or row == 0);
}

bool GameBoard::attach(const size_t row, const size_t col, const size_t hue) {
    if (canAttach(row, col)) {
        set(row, col, hue);
        return true;
    }

    return false;
}

bool GameBoard::pop(const size_t row, const size_t col, const size_t matches) {
    // NOTE: this DFS explores all connected bubbles of the same hue, and pops them if they are enough
    if (board[at(row, col)] == 0)
        return false;

    const size_t matchHue = board[at(row, col)].hue;

    std::vector<std::pair<size_t, size_t>> dfs, found;

    dfs.push_back({row, col});
    while (!dfs.empty()) {
        const std::pair<size_t, size_t> el = dfs.back();
        dfs.pop_back();

        // NOTE: awkward, but uses less memory than a visited set by using the existing board state
        if (oob(el.first, el.second) or board[at(el.first, el.second)].hue != matchHue)
            continue;

        found.push_back(el);

        for (const std::pair<int, int>& of : getOffsets(el.first))
            dfs.push_back({ el.first + of.first, el.second + of.second });

        set(el.first, el.second, 0);
    }

    if (found.size() >= (matches == 0 ? matchesToPop : matches))
        return true;
    
    for (const std::pair<size_t, size_t>& el : found)
        set(el.first, el.second, matchHue);

    return false;
}

void GameBoard::dropFloating() {
    // NOTE: this DFS starts from just the 0th row, removes anything it cannot reach
    
    // NOTE: uses the drop updated board as a visit tracker
    std::vector<BubbleCell> dropped(board.size(), {0, 0});
    std::vector<std::pair<size_t, size_t>> dfs;

    for (size_t col = 0; col < cols; col++)
        if (board[at(0, col)] != 0)
            dfs.push_back({0, col});

    while (!dfs.empty()) {
        const std::pair<size_t, size_t> el = dfs.back();
        dfs.pop_back();

        if (oob(el.first, el.second) 
            or board[at(el.first, el.second)] == 0 
            or dropped[at(el.first, el.second)] != 0)
            continue;

        dropped[at(el.first, el.second)].hue = board[at(el.first, el.second)].hue;

        applyNbrs(dropped, el.first, el.second);

        for (const std::pair<int, int>& of : getOffsets(el.first))
            dfs.push_back({ el.first + of.first, el.second + of.second });
    }

    board = std::move(dropped);
}

bool GameBoard::reachedBottom() const {
    for (size_t col = 0; col < getColAlign(rows - 1); col++)
        if (board[at(rows - 1, col)] != 0)
            return true;

    return false;
}

bool GameBoard::update(const size_t row, const size_t col, const size_t hue, const size_t matches) {
    if (attach(row, col, hue)) {
        if (pop(row, col, matches))
            dropFloating();
        return true;
    }

    return false;
}

void GameBoard::clear() {
    for (BubbleCell& cell : board)
        cell = {0, 0};
}

/* --- protected --- */

size_t GameBoard::at(const size_t row, const size_t col) const {
    if (oob(row, col))
        throw std::out_of_range("Requested GameBoard::at(" + std::to_string(row) + ", " + std::to_string(col) + ") position is out of bounds.");

    return getGridSize(row) + col;
}

void GameBoard::applyNbrs(std::vector<BubbleCell>& b, const size_t row, const size_t col) {
    // TODO: Do not run multiple times on the same hue
    for (const std::pair<int, int>& of : getOffsets(row)) {
        if (oob(row + of.first, col + of.second) or oob(row, col))
            continue;

        b[at(row + of.first, col + of.second)].neighbors += b[at(row, col)] == 0 ? -1 : 1;
    }
}

std::array<std::pair<int, int>, 6> GameBoard::getOffsets(const size_t row) const {
    return {
        std::pair<int, int>{0, -1}, std::pair<int, int>{0, 1}, 
        std::pair<int, int>{-1, 0}, std::pair<int, int>{1, 0}, 
        std::pair<int, int>{-1, (row % 2 == 0 ? -1 : 1)}, std::pair<int, int>{1, (row % 2 == 0 ? -1 : 1)}
    };
}