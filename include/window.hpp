#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <string>

#include "action.hpp"
#include "board.hpp"
#include "util.hpp"

#include <raylib.h>

class GameWindow {
public:
    GameWindow(const float width = DEFAULT_WIDTH, const float height = DEFAULT_HEIGHT, const size_t rows = DEFAULT_ROWS, const size_t cols = DEFAULT_COLS, const char* title = DEFAULT_TITLE, size_t fps = DEFAULT_FPS);
    ~GameWindow();

    void run();

    void drawText(const std::string text, const float x, const float y, const float scale = 1.0f, const Color color = WHITE);
    void drawBubble(const float x, const float y, const size_t hue);
    void drawBoard();
    void drawActions();

protected:
    static constexpr float DEFAULT_WIDTH = 600.0f;
    static constexpr float DEFAULT_HEIGHT = 960.0f;
    static constexpr const char* DEFAULT_TITLE = "Game Window";
    static constexpr size_t DEFAULT_FPS = 60;

    static constexpr const char* FONT_PATH = "res/fonts/ct_prolamina.ttf";
    static constexpr size_t FONT_SIZE = 48;

    static constexpr size_t BUBBLE_TEX_COUNT = 6;
    static constexpr const char* BUBBLE_TEX_PATHS[BUBBLE_TEX_COUNT] = {
        "res/sprites/bubble_1.png",
        "res/sprites/bubble_2.png",
        "res/sprites/bubble_3.png",
        "res/sprites/bubble_4.png",
        "res/sprites/bubble_5.png",
        "res/sprites/bubble_6.png"
    };

    static constexpr size_t DEFAULT_ROWS = 140;
    static constexpr size_t DEFAULT_COLS = 100;

    float width;
    float height;
    size_t fps;
    float radius;

    Font font;
    Texture2D bubbleTexs[BUBBLE_TEX_COUNT];

    GameBoard board;
    GameActionMgr actions;

    float limitLineY;

    //inline void drawDebugOverlay();
    //inline void drawDebugBouncy(const size_t hue = 1);
};

#endif