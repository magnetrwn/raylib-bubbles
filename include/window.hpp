#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <string>

#include "action.hpp"
#include "board.hpp"
#include "util.hpp"

#include <raylib.h>

class GameWindow {
public:
    GameWindow(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, const char* title = DEFAULT_TITLE, int fps = DEFAULT_FPS);
    ~GameWindow();

    void run();

    void drawText(const std::string text, const float x, const float y, const float scale = 1.0f, const Color color = WHITE);
    void drawBubble(const float x, const float y, const float radius, const Color color = WHITE);

    void drawBoard(); // TODO: figure out why this cannot be const

    int xToCol(const float x) const;
    int yToRow(const float y) const;

protected:
    static constexpr int DEFAULT_WIDTH = 480;
    static constexpr int DEFAULT_HEIGHT = 720;
    static constexpr const char* DEFAULT_TITLE = "Game Window";
    static constexpr int DEFAULT_FPS = 60;

    static constexpr const char* DEFAULT_FONT_PATH = "res/ct_prolamina.ttf";
    static constexpr int DEFAULT_FONT_SIZE = 48;
    static constexpr const char* DEFAULT_BUBBLE_TEX_PATH = "res/bubble.png";

    int width;
    int height;
    int fps;

    Font font;
    Texture2D bubble;

    GameBoard board;
    GameActionMgr actions;

    // TODO: we need a way to figure out what the size of each bubble is, based on how 
    //       many are on each row/col, to fit the screen.
};

#endif