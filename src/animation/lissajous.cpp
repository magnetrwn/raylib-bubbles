#include "lissajous.hpp"

LissajousView::Float2 LissajousView::step() {
    float x = (background.x - viewport.x) / 2 * std::sin(params.a * t + params.delta) + (background.x - viewport.x) / 2;
    float y = (background.y - viewport.y) / 2 * std::sin(params.b * t) + (background.y - viewport.y) / 2;
    t += params.speed;
    return {x, y};
}

void LissajousView::change(const Float2 viewport, const Float2 background) {
    this->viewport = viewport;
    this->background = background;
}
