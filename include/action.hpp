#ifndef ACTION_HPP_
#define ACTION_HPP_

#include <array>
#include <list>

#include "board.hpp"

class GameActionMgr {
public:
    struct ActionType {
        static constexpr int EFFECT_DATA_SIZE = 7;

        /* Data held by the array will depend on the effect:
         *
         * LAUNCH: {      x,      y,  angle, radius,   xVel,   yVel }
         * LINEAR: {  fromX,  fromY,    toX,    toY, radius,   xVel,   yVel }
         * DROP:   {      x,      y, radius }
         *
         * So we make an array of 7 floats and only use based on effect.
         * The first two elements will always be changing on step(), until the effect is done.
         */

        enum class Effect {
            LAUNCH,
            LINEAR,
            DROP
        };

        Effect effect;
        std::array<float, EFFECT_DATA_SIZE> data;
        int hue;

        ActionType(const Effect effect, const std::array<float, EFFECT_DATA_SIZE>& data, const int hue)
            : effect(effect), data(data), hue(hue) {}
    };

    bool isOngoing() const;

    void step();
    void enqueue(const ActionType action);

protected:
    bool ongoing = false;
    std::list<ActionType> actions; // TODO: see if list is better than vector here
};

#endif