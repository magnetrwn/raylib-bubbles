#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <string>

#include "action.hpp"
#include "board.hpp"
#include "util.hpp"

#include <raylib.h>

class GameWindow {
public:
    GameWindow(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, const int rows = DEFAULT_ROWS, const int cols = DEFAULT_COLS, const char* title = DEFAULT_TITLE, int fps = DEFAULT_FPS);
    ~GameWindow();

    void run();

    void drawText(const std::string text, const float x, const float y, const float scale = 1.0f, const Color color = WHITE);
    void drawBubble(const float x, const float y, const int hue = 0);
    void drawBoard();
    void drawLimitLine();

protected:
    static constexpr int DEFAULT_WIDTH = 600;
    static constexpr int DEFAULT_HEIGHT = 800;
    static constexpr const char* DEFAULT_TITLE = "Game Window";
    static constexpr int DEFAULT_FPS = 60;

    static constexpr const char* DEFAULT_FONT_PATH = "res/fonts/ct_prolamina.ttf";
    static constexpr int DEFAULT_FONT_SIZE = 48;

    static constexpr int DEFAULT_BUBBLE_TEX_COUNT = 6;
    static constexpr const char* DEFAULT_BUBBLE_TEX_PATHS[DEFAULT_BUBBLE_TEX_COUNT] = {
        "res/sprites/bubble_0.png",
        "res/sprites/bubble_1.png",
        "res/sprites/bubble_2.png",
        "res/sprites/bubble_3.png",
        "res/sprites/bubble_4.png",
        "res/sprites/bubble_5.png"
    };

    static constexpr int DEFAULT_ROWS = 16;
    static constexpr int DEFAULT_COLS = 12;

    int width;
    int height;
    int fps;
    float radius; // TODO: if you ever want multiple boards, you must add a parameter for this

    Font font;
    Texture2D bubbleTexs[DEFAULT_BUBBLE_TEX_COUNT];

    GameBoard board;
    GameActionMgr actions;

    inline int xyToCol(const float x, const float y) const;
    inline int yToRow(const float y) const;
    inline float rowColToX(const int row, const int col) const;
    inline float rowToY(const int row) const;

    inline void drawDebugOver();
};

#endif