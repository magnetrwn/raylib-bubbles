#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <raylib.h>

class GameWindow {
public:
    GameWindow(int width = DEFAULT_WIDTH, 
        int height = DEFAULT_HEIGHT, 
        const char* title = DEFAULT_TITLE, 
        int fps = DEFAULT_FPS);
    ~GameWindow();

    void run();

protected:
    static constexpr int DEFAULT_WIDTH = 480;
    static constexpr int DEFAULT_HEIGHT = 720;
    static constexpr const char* DEFAULT_TITLE = "Game Window";
    static constexpr int DEFAULT_FPS = 60;

    static constexpr const char* DEFAULT_FONT_PATH = "res/ct_prolamina.ttf";
    static constexpr int DEFAULT_FONT_SIZE = 48;

    int width;
    int height;
    int fps;

    Font font;
};

#endif