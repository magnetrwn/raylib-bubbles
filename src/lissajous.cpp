#include "lissajous.hpp"

LissajousView::Float2 LissajousView::step() {
    float x = (background.x - viewport.x) / 2 * std::sin(a * t + d) + (background.x - viewport.x) / 2;
    float y = (background.y - viewport.y) / 2 * std::sin(b * t) + (background.y - viewport.y) / 2;
    t += speed;
    return {x, y};
}
