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
    void drawBubble(const float x, const float y, const float radius, const Color color = WHITE);
    void drawBoard(const float radius);

protected:
    static constexpr int DEFAULT_WIDTH = 480;
    static constexpr int DEFAULT_HEIGHT = 720;
    static constexpr const char* DEFAULT_TITLE = "Game Window";
    static constexpr int DEFAULT_FPS = 60;

    static constexpr const char* DEFAULT_FONT_PATH = "res/ct_prolamina.ttf";
    static constexpr int DEFAULT_FONT_SIZE = 48;
    static constexpr const char* DEFAULT_BUBBLE_TEX_PATH = "res/bubble.png";

    static constexpr int DEFAULT_ROWS = 10;
    static constexpr int DEFAULT_COLS = 12;

    int width;
    int height;
    int fps;

    Font font;
    Texture2D bubble;

    GameBoard board;
    GameActionMgr actions;

    inline int xyToCol(const float x, const float y, const float radius) const;
    inline int yToRow(const float y, const float radius) const;
    inline float rowColToX(const int row, const int col, const float radius) const;
    inline float rowToY(const int row, const float radius) const;
};

#endif