#include "window.hpp"

/* --- initialization --- */

GameWindow::GameWindow()
    : width(GameUtils::getCfgFloat("Game.Window", "WIDTH")),
      height(GameUtils::getCfgFloat("Game.Window", "HEIGHT")),
      fps(GameUtils::getCfgFloat("Game.Window", "FPS")),
      radius(getFitToWidthR()),
      board(GameUtils::getCfgSizeT("Game.Window.Board", "ROWS"), 
            GameUtils::getCfgSizeT("Game.Window.Board", "COLS")),
      actions(width, height, radius, board),
      limitLineY(GameUtils::rowToY(board.getRows() - 1, radius)) {

    initWindow();
    loadFont();
    loadImages();
    loadTextures();
}

GameWindow::~GameWindow() {
    UnloadFont(font);
    for (const Texture2D& tex : bubbleTexs)
        UnloadTexture(tex);
    for (const Image& img : bgImgs)
        UnloadImage(img);
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

    #ifdef DEBUG_LISSAJOUS
    // TODO: be ready for future dynamic loading using two Texture2D objects
    size_t bgSelected = 0;
    Texture2D bgTex = LoadTextureFromImage(bgImgs[0]);
    LissajousView lissajous(
        { 0.074f, 0.22f, 1.15f, 0.033f },
        { static_cast<float>(width), static_cast<float>(height) }, 
        { static_cast<float>(bgTex.width), static_cast<float>(bgTex.height) }
    );
    #endif

    while (!WindowShouldClose()) {
        BeginDrawing();

            #ifdef DEBUG_LISSAJOUS
            DrawTextureEx(bgTex, { -lissajous.step().x, -lissajous.step().y }, 0.0f, 1.0f, DARKGRAY);
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                lissajous.change(
                    { static_cast<float>(width), static_cast<float>(height) }, 
                    { static_cast<float>(bgTex.width), static_cast<float>(bgTex.height) }
                );
                bgSelected = (bgSelected + 1) % bgImgs.size();
                UnloadTexture(bgTex);
                bgTex = LoadTextureFromImage(bgImgs[bgSelected]);
            }
            #else
            ClearBackground({14, 14, 56, 255});
            #endif
            
            drawBoard();

            #ifdef DEBUG_MOUSESHOOTER
            drawBubble(width / 2 - radius, height - 2 * radius, hueSelected);
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
                hueSelected = 1 + hueSelected % bubbleTexs.size();
            
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
                        static_cast<size_t>(GetRandomValue(1, bubbleTexs.size()))
                    }
                }, actions});
                lastTime = GetTime();
            }
            #endif

            // TODO: insert future game lost
            if (board.reachedBottom())
                board.clear();
            
            drawActions();
            actions.stepAndPrune();

            #ifdef DEBUG_SHOW_INFO
            drawText(std::to_string(GetFPS()), 15.0f, 8.0f, 1.0f, LIME);
            drawText(std::to_string(actions.size()), 15.0f, height - 55.0f, 1.0f, GOLD);
            drawText(std::to_string(board.count()), 115.0f, height - 55.0f, 1.0f, LIGHTGRAY);
            drawText("EARLY", width - 145.0f, height - 55.0f, 1.0f, RED);
            #endif

        EndDrawing();
    }
}

void GameWindow::drawText(const std::string& text, const float x, const float y, const float scale, const Color& color) {
    DrawTextEx(font, text.c_str(), { x, y }, font.baseSize * scale, 1, color);
}

void GameWindow::drawBubble(const float x, const float y, const size_t hue) {
    if (hue == 0)
        return;

    if (hue > bubbleTexs.size())
        throw std::invalid_argument("Requested GameWindow::drawBubble() hue (texture index) is not between 0 and " + std::to_string(bubbleTexs.size()) + ".");

    DrawTextureEx(bubbleTexs[hue - 1], { x, y }, 0.0f, 2 * radius / bubbleTexs[0].width, WHITE);
}

void GameWindow::drawBoard() {
    DrawLine(0, limitLineY, width, limitLineY, RED);

    for (size_t row = 0; row < board.getRows(); row++)
        for (size_t col = 0; col < board.getColAlign(row); col++) {
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

/* --- protected --- */

void GameWindow::initWindow() {
    SetTargetFPS(fps);
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(width, height, GameUtils::getCfgStr("Game.Window", "TITLE").c_str());
    TraceLog(LOG_INFO, ("Executable directory: " + GameUtils::getAbsDir()).c_str());
}

void GameWindow::loadFont() {
    font = LoadFontEx((GameUtils::getAbsDir() + GameUtils::getCfgStr("Game.Window.Font", "PATH")).c_str(), 
                      GameUtils::getCfgSizeT("Game.Window.Font", "SIZE"), nullptr, 0);
}

void GameWindow::loadImages() {
    std::string path;
    std::istringstream bgImgPaths(GameUtils::getCfgStr("Game.Window.Background", "PATHS"));
    while (std::getline(bgImgPaths, path, ':'))
        bgImgs.push_back(LoadImage((GameUtils::getAbsDir() + path).c_str()));
}

void GameWindow::loadTextures() {
    std::string path;
    std::istringstream bubbleTexPaths(GameUtils::getCfgStr("Game.Window.Bubble", "PATHS"));
    while (std::getline(bubbleTexPaths, path, ':'))
        bubbleTexs.push_back(LoadTexture((GameUtils::getAbsDir() + path).c_str()));
}

float GameWindow::getFitToWidthR() const {
    // NOTE: this calculates the radius to give the board a fit-to-width appearance;
    //       keep in mind that bubble coords for textures on the board are distanced by 2 * radius to each other!
    const size_t cols = GameUtils::getCfgSizeT("Game.Window.Board", "COLS");
    return width / (static_cast<float>(cols) + (cols % 2 == 1 ? 0.5f : 0)) / 2.0f;
}
