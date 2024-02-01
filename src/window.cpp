#include "window.hpp"

/* --- initialization --- */

GameWindow::GameWindow(const int width, const int height, const char* title, const int fps) 
    : width(width), height(height), fps(fps) {

    InitWindow(width, height, title);
    SetTargetFPS(fps);
    font = LoadFontEx(DEFAULT_FONT_PATH, DEFAULT_FONT_SIZE, nullptr, 0);
    //bubble = LoadTexture("res/b_none.png");
}

GameWindow::~GameWindow() {
    UnloadFont(font);
    CloseWindow();
}

/* --- public --- */

void GameWindow::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(DARKGREEN);
            DrawTextEx(font, "What's UP! ~¿!", {24, 64}, font.baseSize, 1, GOLD);
            
            DrawCircleV({100.0f, 200.0f}, 50.0f, LIGHTGRAY);
            //DrawTexture(bubble, 100.0f - bubble.width / 2, 200.0f - bubble.height / 2, WHITE);

        EndDrawing();
    }
}
