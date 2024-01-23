#include "window.hpp"

GameWindow::GameWindow(const std::size_t width, const std::size_t height, const char* title, const std::size_t fps) 
    : width(width), height(height), fps(fps) {

    InitWindow(width, height, title);
    SetTargetFPS(fps);
    font = LoadFontEx(DEFAULT_FONT_PATH, DEFAULT_FONT_SIZE, NULL, 0);
}

void GameWindow::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGREEN);
        DrawTextEx(font, "What's UP! ~¿!", {24, 64}, font.baseSize, 1, GOLD);
        EndDrawing();
    }
}

GameWindow::~GameWindow() {
    UnloadFont(font);
    CloseWindow();
}
