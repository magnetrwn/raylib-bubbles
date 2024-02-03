#include "window.hpp"

/* --- initialization --- */

GameWindow::GameWindow(const int width, const int height, const int rows, const int cols, const char* title, const int fps) 
    : width(width), height(height), fps(fps), board(rows, cols) {

    InitWindow(width, height, title);
    SetTargetFPS(fps);
    font = LoadFontEx(DEFAULT_FONT_PATH, DEFAULT_FONT_SIZE, nullptr, 0);
    bubble = LoadTexture(DEFAULT_BUBBLE_TEX_PATH);
}

GameWindow::~GameWindow() {
    UnloadFont(font);
    CloseWindow();
}

/* --- public --- */

void GameWindow::run() {
    Vector2 test = { static_cast<float>(width) / 2, static_cast<float>(height) / 2 };
    float radius = static_cast<float>(width) / board.getCols() / 2;
    float xvel = -0.2f;
    float yvel = -0.2f;

    while (!WindowShouldClose()) {
        test.x += xvel;
        test.y += yvel;

        if (GameUtils::clamp(test.x, 0, width - 2 * radius))
            xvel *= -1;
        if (GameUtils::clamp(test.y, 0, height - 2 * radius))
            yvel *= -1;

        BeginDrawing();
            ClearBackground(BLACK);

            drawBoard(radius);
            drawText("col: " + std::to_string(xyToCol(test.x, test.y, radius)) + ", row: " + std::to_string(yToRow(test.y, radius)),
                     20.0f, static_cast<float>(height) - 64.0f);
            drawBubble(test.x, test.y, radius);

        EndDrawing();
    }
}

void GameWindow::drawText(const std::string text, const float x, const float y, const float scale, const Color color) {
    DrawTextEx(font, text.c_str(), { x, y }, font.baseSize * scale, 1, color);
}

void GameWindow::drawBubble(const float x, const float y, const float radius, const Color color) {
    DrawTextureEx(bubble, { x, y }, 0.0f, 2 * radius / bubble.width, color);
}

void GameWindow::drawBoard(const float radius) {
    for (int row = 0; row < board.getRows(); row++) {
        for (int col = 0; col < board.hexAlign(row); col++)
            //if (hue != 0)
                drawBubble(
                    rowColToX(row, col, radius), 
                    rowToY(row, radius), radius, 
                    GameUtils::asRaylibColor(board.get(row, col))
                );
    }
}

/* --- protected --- */

int GameWindow::xyToCol(const float x, const float y, const float radius) const {
    return static_cast<int>((x - (yToRow(y, radius) % 2 == 0 ? 0 : radius)) / (2 * radius));
}

int GameWindow::yToRow(const float y, const float radius) const {
    return static_cast<int>(y / (2 * radius));
}

float GameWindow::rowColToX(const int row, const int col, const float radius) const {
    return static_cast<float>(col * 2) * radius + (row % 2 == 0 ? 0.0f : radius);
}

float GameWindow::rowToY(const int row, const float radius) const {
    return static_cast<float>(row * 2) * radius;
}
