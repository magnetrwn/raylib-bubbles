#include "window.hpp"
#include "action.hpp"
#include <ctime>
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
    double lastTime = GetTime();

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            
            drawBoard();
            if (GetTime() - lastTime >= 0.002f) {
                //TraceLog(LOG_INFO, std::to_string(GetTime() - lastTime).c_str());
                actions.enqueue({GameActionMgr::ActionType::Effect::LAUNCH, {
                {
                        width / 2, height - 2 * radius, 
                        static_cast<float>(GetRandomValue(0, RAND_MAX) / static_cast<float>(RAND_MAX) * 4.0f - 2.0f) * 5.0f, 
                        static_cast<float>(GetRandomValue(0, RAND_MAX) / static_cast<float>(RAND_MAX) * -5.0f) * 3.0f,
                        static_cast<size_t>(GetRandomValue(1, BUBBLE_TEX_COUNT))
                    }
                }, actions});
                lastTime = GetTime();
            }
            
            drawActions();
            actions.stepAndPrune();

            drawText(std::to_string(actions.size()), 20.0f, height - 80.0f, 1.5f, GOLD);

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
        }
}

void GameWindow::drawActions() {
    for (const GameActionMgr::BubbleData& bubble : actions.getAllStepData())
        drawBubble(bubble.x, bubble.y, bubble.hue);
}

/*
void GameWindow::drawDebugOverlay() {
    Vector2 mousePos = GetMousePosition();
    drawText("col: " + std::to_string(xyToCol(mousePos.x, mousePos.y)) + ", row: " + std::to_string(yToRow(mousePos.y)),
        20.0f, height - 64.0f);
    drawBubble(mousePos.x, mousePos.y, 1);
}

void GameWindow::drawDebugBouncy(const size_t hue) {
    static Vector2 bouncy = { width / 2, height / 2 };
    static float xvel = -5.0f;
    static float yvel = -4.0f;

    bouncy.x += xvel;
    bouncy.y += yvel;

    if (GameUtils::clamp(bouncy.x, 0, width - 2 * radius))
        xvel *= -1;
    if (GameUtils::clamp(bouncy.y, 0, height - 2 * radius))
        yvel *= -1;

    drawBubble(bouncy.x, bouncy.y, hue);

    try {
        const size_t row = yToRow(bouncy.y);
        const size_t col = xyToCol(bouncy.x, bouncy.y);

        if (!GameUtils::usedLast(row, col) and board.get(row, col) == 0)
            board.setThenPop(row, col, GetRandomValue(1, 4));

    } catch (const std::out_of_range& e) {}
}*/