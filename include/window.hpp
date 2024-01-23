#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <cstddef>
#include <string>
#include <raylib.h>

class GameWindow {
protected:
    static constexpr std::size_t DEFAULT_WIDTH = 480;
    static constexpr std::size_t DEFAULT_HEIGHT = 720;
    static constexpr const char* DEFAULT_TITLE = "Game Window";
    static constexpr std::size_t DEFAULT_FPS = 60;

    static constexpr const char* DEFAULT_FONT_PATH = "res/ct_prolamina.ttf";
    static constexpr std::size_t DEFAULT_FONT_SIZE = 48;

    std::size_t width;
    std::size_t height;
    std::size_t fps;

    Font font;
    
public:
    GameWindow(std::size_t width = DEFAULT_WIDTH, 
        std::size_t height = DEFAULT_HEIGHT, 
        const char* title = DEFAULT_TITLE, 
        std::size_t fps = DEFAULT_FPS);
    ~GameWindow();

    void run();
};

#endif