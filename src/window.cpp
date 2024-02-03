#include "window.hpp"

/* --- initialization --- */

GameWindow::GameWindow(const int width, const int height, const char* title, const int fps) 
    : width(width), height(height), fps(fps) {

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
    float radius = 32.0f;
    float xvel = 2.6f;
    float yvel = -1.1f;

    while (!WindowShouldClose()) {
        test.x += xvel;
        test.y += yvel;

        if (GameUtils::clamp(test.x, 0, width - 2 * radius))
            xvel *= -1;
        if (GameUtils::clamp(test.y, 0, height - 2 * radius))
            yvel *= -1;

        BeginDrawing();
            ClearBackground(BLACK);

            drawText("col: " + std::to_string(xToCol(test.x)) + ", row: " + std::to_string(yToRow(test.y)),
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

void GameWindow::drawBoard() {
    for (int row = 0; row < board.getRows(); row++) {
        for (int col = 0; col < board.getCols(); col++) {
            const float x = col * (static_cast<float>(width) / board.getCols());
            const float y = row * (static_cast<float>(height) / board.getRows());
            const float radius = 32.0f;
            const int hue = board.get(row, col);

            if (hue != 0) {
                drawBubble(x, y, radius, GameUtils::asRaylibColor(hue));
            }
        }
    }
}

int GameWindow::xToCol(const float x) const {
    return static_cast<int>(x / (static_cast<float>(width) / board.getCols()));
}

int GameWindow::yToRow(const float y) const {
    return static_cast<int>(y / (static_cast<float>(height) / board.getRows()));
}