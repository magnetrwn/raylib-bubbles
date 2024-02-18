#include "board.hpp"
#include <cstddef>

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

    applyNbr(row, col, row, col - 1);
    applyNbr(row, col, row, col + 1);
    applyNbr(row, col, row - 1, col);
    applyNbr(row, col, row + 1, col);
    applyNbr(row, col, row - 1, col + (row % 2 == 0 ? -1 : 1));
    applyNbr(row, col, row + 1, col + (row % 2 == 0 ? -1 : 1));
}

bool GameBoard::attach(const size_t row, const size_t col, const size_t hue) {
    if (board[at(row, col)] == 0 and (board[at(row, col)].neighbors != 0 or row == 0)) {
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

    return false;
}

void GameBoard::dropFloating() {
    // NOTE: this DFS tries to reach the top row of the board on all cells
    
    std::unordered_set<size_t> visited;

    for (size_t row = 0; row < rows; row++)
        for (size_t col = 0; col < hexAlign(row); col++) {

            if (visited.find(at(row, col)) != visited.end() or board[at(row, col)] == 0)
                continue;

            std::vector<std::pair<size_t, size_t>> dfs, found;

            dfs.push_back({row, col});
            while (!dfs.empty()) {
                const std::pair<size_t, size_t> el = dfs.back();
                dfs.pop_back();

                if (visited.find(at(el.first, el.second)) != visited.end() or board[at(el.first, el.second)] == 0)
                    continue;

                if (el.first == 0) {
                    found.clear();
                    break;
                }

                found.push_back(el);
                visited.insert(at(el.first, el.second));

                dfs.push_back({ el.first, el.second - 1 });
                dfs.push_back({ el.first, el.second + 1 });
                dfs.push_back({ el.first - 1, el.second });
                dfs.push_back({ el.first + 1, el.second });
                dfs.push_back({ el.first - 1, el.second + (el.first % 2 == 0 ? -1 : 1) });
                dfs.push_back({ el.first + 1, el.second + (el.first % 2 == 0 ? -1 : 1) });
            }

            for (const std::pair<size_t, size_t>& el : found)
                set(el.first, el.second, 0);
        }
}

/*
bool GameBoard::slide(const size_t row, const size_t col) {

    for (size_t r = row; r > 0; r--)
        std::swap(board[at(r, col)], board[at(r - 1, col)]);

}
*/

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

bool GameBoard::oob(const size_t row, const size_t col) const {
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

    board[at(dstRow, dstCol)].neighbors += board[at(srcRow, srcCol)] == 0 ? -1 : 1;
}

bool GameBoard::compare(const size_t row, const size_t col, const int rowOffset, const int colOffset) const {
    return board[at(row, col)] == board[at(row + rowOffset, col + colOffset)];
}