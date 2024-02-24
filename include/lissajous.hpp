#ifndef LISSAJOUS_HPP_
#define LISSAJOUS_HPP_

#include <cmath>

class LissajousView {
public:
    struct Float2 {
        float x;
        float y;
    };

    LissajousView(const float a, const float b, const float d, const Float2 viewport, const Float2 background, const float speed = 0.02f) 
        : a(a), b(b), d(d), viewport(viewport), background(background), speed(speed), t(0.0f) {}

    Float2 step();

protected:
    const float a;
    const float b;
    const float d;
    const Float2 viewport;
    const Float2 background;
    const float speed;
    
    float t;
};

#endif