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
        : a(a), b(b), d(d), speed(speed), viewport(viewport), background(background), t(0.0f) {}

    Float2 step();

    void change(const Float2 viewport, const Float2 background);

protected:
    const float a;
    const float b;
    const float d;
    const float speed;
    
    Float2 viewport;
    Float2 background;

    float t;
};

#endif