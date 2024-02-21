#include "window.hpp"
#include <raylib.h>

constexpr const char* GameWindow::BUBBLE_TEX_PATHS[BUBBLE_TEX_COUNT];

/* --- initialization --- */

GameWindow::GameWindow(const float width, const float height, const size_t rows, const size_t cols, const char* title, const size_t fps) 
    : width(width), height(height), fps(fps), 
      radius(width / (static_cast<float>(cols) + (cols % 2 == 1 ? 0.5f : 0)) / 2.0f), // NOTE: radius to fit-to-width
      board(rows, cols), actions(width, height, radius, board),
      limitLineY(GameUtils::rowToY(board.getRows() - 1, radius)) {

    InitWindow(width, height, title);
    SetTargetFPS(fps);

    font = LoadFontEx(FONT_PATH, FONT_SIZE, nullptr, 0);
    for (size_t i = 0; i < BUBBLE_TEX_COUNT; i++)
        bubbleTexs[i] = LoadTexture(BUBBLE_TEX_PATHS[i]);
}

GameWindow::~GameWindow() {
    UnloadFont(font);
    for (size_t i = 0; i < BUBBLE_TEX_COUNT; i++)
        UnloadTexture(bubbleTexs[i]);
    CloseWindow();
}

/* --- public --- */

void GameWindow::run() {
    #ifdef DEBUG_MOUSESHOOTER
    size_t hueSelected = 1;
    #endif

    #ifdef DEBUG_SPRINKLER
    double lastTime = GetTime();
    #endif

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            
            drawBoard();

            #ifdef DEBUG_MOUSESHOOTER
            drawBubble(width / 2 - radius, height - 2 * radius, hueSelected);
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
                hueSelected = 1 + hueSelected % BUBBLE_TEX_COUNT;
            
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                actions.enqueue({GameActionMgr::ActionType::Effect::LAUNCH, {
                {
                        width / 2 - radius, height - 2 * radius, 
                        (GetMousePosition().x - width / 2) / 30.0f,
                        (GetMousePosition().y - height) / 30.0f,
                        static_cast<size_t>(hueSelected)
                    }
                }, actions});
            #endif

            #ifdef DEBUG_SPRINKLER
            if (GetTime() - lastTime > 0.375f and actions.size() < 5) {
                const float direction = static_cast<float>(GetRandomValue(0, RAND_MAX) / static_cast<float>(RAND_MAX)) * 1.57f - 0.79f;
                const float speed = 8.0f;
                actions.enqueue({GameActionMgr::ActionType::Effect::LAUNCH, {
                {
                        width / 2 - radius, height - 2 * radius, 
                        std::sin(direction) * speed, 
                        std::cos(direction) * -speed,
                        static_cast<size_t>(GetRandomValue(1, BUBBLE_TEX_COUNT))
                    }
                }, actions});
                lastTime = GetTime();
            }
            #endif

            if (board.reachedBottom())
                board.clear();
            
            drawActions();
            actions.stepAndPrune();

        EndDrawing();
    }
}

void GameWindow::drawText(const std::string text, const float x, const float y, const float scale, const Color color) {
    DrawTextEx(font, text.c_str(), { x, y }, font.baseSize * scale, 1, color);
}

void GameWindow::drawBubble(const float x, const float y, const size_t hue) {
    if (hue == 0)
        return;

    if (hue > BUBBLE_TEX_COUNT)
        throw std::invalid_argument("Requested GameWindow::drawBubble() hue (texture index) is not between 0 and " + std::to_string(BUBBLE_TEX_COUNT) + ".");

    DrawTextureEx(bubbleTexs[hue - 1], { x, y }, 0.0f, 2 * radius / bubbleTexs[0].width, WHITE);
}

void GameWindow::drawBoard() {
    DrawLine(0, limitLineY, width, limitLineY, RED);

    for (size_t row = 0; row < board.getRows(); row++)
        for (size_t col = 0; col < board.hexAlign(row); col++) {
            size_t hue = board.get(row, col);

            if (hue != 0)
                drawBubble(GameUtils::rowColToX(row, col, radius), GameUtils::rowToY(row, radius), hue);

            // drawText(std::to_string(board.getNbrs(row, col)), GameUtils::rowColToX(row, col, radius), GameUtils::rowToY(row, radius), 0.5f, LIGHTGRAY);
        }
}

void GameWindow::drawActions() {
    for (const GameActionMgr::BubbleData& bubble : actions.getAllStepData())
        drawBubble(bubble.x, bubble.y, bubble.hue);
}