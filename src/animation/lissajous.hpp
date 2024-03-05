#ifndef LISSAJOUS_HPP_
#define LISSAJOUS_HPP_

#include <cmath>

class LissajousView {
public:
    struct LissajousInit {
        float a;
        float b;
        float delta;
        float speed;
    };

    struct Float2 {
        float x;
        float y;
    };

    LissajousView(const LissajousInit params, const Float2 viewport, const Float2 background) 
        : params(params), viewport(viewport), background(background), t(0.0f) {}

    Float2 step();

    void change(const Float2 viewport, const Float2 background);

protected:
    const LissajousInit params;

    Float2 viewport;
    Float2 background;

    float t;
};

#endif