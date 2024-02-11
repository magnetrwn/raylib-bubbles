#ifndef ACTION_HPP_
#define ACTION_HPP_

#include <array>
#include <list>

#include "board.hpp"

class GameActionMgr {
public:
    struct ActionType {
        static constexpr size_t EFFECT_DATA_SIZE = 7;

        /* The Effect enum determines the effect type, and represents:
         *
         * LAUNCH: a bubble is launched from the cannon, moves upwards at an angle, bounces off walls,
         *         and attaches to the board according to where it hits.
         * DROP: animation for bubbles left floating on the board, dropping with parabolic motion.
         *
         * Data held by the array will depend on the effect:
         *
         * LAUNCH: {      x,      y, radius,   xVel,   yVel }
         * DROP:   {      x,      y, radius }
         *
         * So we make an array of 7 floats and only use based on effect.
         * The first two elements will always be changing on step(), until the effect is done.
         */

        enum class Effect {
            LAUNCH,
            DROP
        };

        Effect effect;
        std::array<float, EFFECT_DATA_SIZE> data;
        size_t hue;

        ActionType(const Effect effect, const std::array<float, EFFECT_DATA_SIZE>& data, const size_t hue)
            : effect(effect), data(data), hue(hue) {}

        ActionType(const Effect effect, std::array<float, EFFECT_DATA_SIZE>&& data, const size_t hue)
            : effect(effect), data(std::move(data)), hue(hue) {}
    };

    bool isOngoing() const;

    void step();
    void enqueue(const ActionType action);

protected:
    bool ongoing = false;
    std::list<ActionType> actions; // TODO: see if list is better than vector here
};

#endif