#ifndef ACTION_HPP_
#define ACTION_HPP_

#include <vector>
#include <tuple>
#include <algorithm>

#include "board.hpp"

// NOTE: std::tuple<size_t /*row*/, size_t /*col*/, size_t /*hue*/>

class GameActionMgr {
public:
    struct ActionType {
        enum class Effect {
            LAUNCH,
            POP,
            DROP
        };

        Effect effect;
        std::vector<std::tuple<size_t, size_t, size_t>> bubbleData;
        
        void step();
    };

    GameActionMgr(const float width, const float height) : width(width), height(height) {};

    void enqueue(const ActionType action);
    void stepAndPrune();

protected:
    float width;
    float height;

    std::vector<ActionType> actions;

    bool shouldPrune(const ActionType& action) const;
};

#endif