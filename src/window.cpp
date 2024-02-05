#include "window.hpp"
#include <raylib.h>

constexpr const char* GameWindow::BUBBLE_TEX_PATHS[BUBBLE_TEX_COUNT];

/* --- initialization --- */

GameWindow::GameWindow(const int width, const int height, const int rows, const int cols, const char* title, const int fps) 
    : width(width), height(height), fps(fps), board(rows, cols) {

    InitWindow(width, height, title);
    SetTargetFPS(fps);

    font = LoadFontEx(FONT_PATH, FONT_SIZE, nullptr, 0);
    for (int i = 0; i < BUBBLE_TEX_COUNT; i++)
        bubbleTexs[i] = LoadTexture(BUBBLE_TEX_PATHS[i]); // TODO: remember to move int back to size_t the whole project.

    radius = static_cast<float>(width) / (static_cast<float>(cols) + (cols % 2 == 1 ? 0.5f : 0)) / 2.0f; // NOTE: fit-to-width
}

GameWindow::~GameWindow() {
    UnloadFont(font);
    for (int i = 0; i < BUBBLE_TEX_COUNT; i++)
        UnloadTexture(bubbleTexs[i]);
    CloseWindow();
}

/* --- public --- */

void GameWindow::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            
            drawBoard();
            drawDebugBouncy();
            drawDebugOverlay();

        EndDrawing();
    }
}

void GameWindow::drawText(const std::string text, const float x, const float y, const float scale, const Color color) {
    DrawTextEx(font, text.c_str(), { x, y }, font.baseSize * scale, 1, color);
}

void GameWindow::drawBubble(const float x, const float y, const int hue) {
    if (hue == 0)
        return;

    if (hue < 0 or hue > BUBBLE_TEX_COUNT)
        throw std::invalid_argument("Requested GameWindow::drawBubble() hue (texture index) is not between 0 and " + std::to_string(BUBBLE_TEX_COUNT) + ".");

    DrawTextureEx(bubbleTexs[hue - 1], { x, y }, 0.0f, 2 * radius / bubbleTexs[0].width, WHITE);
}

void GameWindow::drawBoard() {
    DrawLine(0, rowToY(board.getRows() - 1), width, rowToY(board.getRows() - 1), RED);

    for (int row = 0; row < board.getRows(); row++)
        for (int col = 0; col < board.hexAlign(row); col++)
            //if (hue != 0)
                drawBubble(
                    rowColToX(row, col), 
                    rowToY(row), 
                    board.get(row, col)
                );
}

/* --- protected --- */

int GameWindow::xyToCol(const float x, const float y) const {
    return static_cast<int>((x - (yToRow(y) % 2 == 0 ? 0 : radius)) / (2 * radius));
}

int GameWindow::yToRow(const float y) const {
    return static_cast<int>(y / (2 * radius));
}

float GameWindow::rowColToX(const int row, const int col) const {
    return static_cast<float>(col * 2) * radius + (row % 2 == 0 ? 0.0f : radius);
}

float GameWindow::rowToY(const int row) const {
    return static_cast<float>(row * 2) * radius;
}

void GameWindow::drawDebugOverlay() {
    Vector2 mousePos = GetMousePosition();
    drawText("col: " + std::to_string(xyToCol(mousePos.x, mousePos.y)) + ", row: " + std::to_string(yToRow(mousePos.y)),
        20.0f, static_cast<float>(height) - 64.0f);
    drawBubble(mousePos.x, mousePos.y, 1);
}

void GameWindow::drawDebugBouncy(const int hue) {
    static Vector2 bouncy = { static_cast<float>(width) / 2, static_cast<float>(height) / 2 };
    static float xvel = -3.3f;
    static float yvel = -1.3f;

    bouncy.x += xvel;
    bouncy.y += yvel;

    if (GameUtils::clamp(bouncy.x, 0, width - 2 * radius))
        xvel *= -1;
    if (GameUtils::clamp(bouncy.y, 0, height - 2 * radius))
        yvel *= -1;

    drawBubble(bouncy.x, bouncy.y, hue);

    try {
        if (board.get(yToRow(bouncy.y), xyToCol(bouncy.x, bouncy.y)) == 0)
            board.set(yToRow(bouncy.y), xyToCol(bouncy.x, bouncy.y), GetRandomValue(1, BUBBLE_TEX_COUNT));
    } catch (const std::out_of_range& e) {}
}