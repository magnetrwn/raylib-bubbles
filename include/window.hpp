#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <string>
#include <sstream>
#include <cmath>

#include <raylib.h>

#include "action.hpp"
#include "board.hpp"
#include "util.hpp"
#include "lissajous.hpp"

class GameWindow {
public:
    GameWindow();
    ~GameWindow();

    void run();

    void drawText(const std::string& text, const float x, const float y, const float scale = 1.0f, const Color& color = WHITE);
    void drawBubble(const float x, const float y, const size_t hue);
    void drawBoard();
    void drawActions();

protected:
    const float width;
    const float height;
    const size_t fps;
    const float radius;

    Font font;
    std::vector<Image> bgImgs;
    std::vector<Texture2D> bubbleTexs;

    GameBoard board;
    GameActionMgr actions;

    const float limitLineY;

    void initWindow();
    void loadFont();
    void loadImages();
    void loadTextures();

    float getFitToWidthR() const;
};

#endif