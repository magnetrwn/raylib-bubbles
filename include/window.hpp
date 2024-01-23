#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <cstddef>
#include <string>
#include <raylib.h>

class GameWindow {
protected:
    std::size_t width;
    std::size_t height;
    std::size_t fps;

    std::string title;

    Font font;
    
public:
    GameWindow(std::size_t width = 480, std::size_t height = 720, const std::string& title = "Game Window", std::size_t fps = 60);
    ~GameWindow();

    void run();
};

#endif