#ifndef ACTION_HPP_
#define ACTION_HPP_

#include <vector>
#include <tuple>
#include <algorithm>
#include <list>
#include <stdexcept>

#include "board.hpp"
#include "util.hpp"

class GameActionMgr {
public:
    struct BubbleData {
        float x;
        float y;
        float xVel;
        float yVel;
        size_t hue;
    };

    struct ActionType {
        enum class Effect {
            LAUNCH
        };

        const Effect effect;
        const GameActionMgr& parent;
        std::vector<BubbleData> bubbleData;
        bool pruneFlag = false;

        ActionType(const Effect effect, const std::vector<BubbleData>& bubbleData, const GameActionMgr& mgr) : effect(effect), parent(mgr), bubbleData(bubbleData) {};

        void step();

        bool shouldPrune() const;
    };

    GameActionMgr(const float width, const float height, const float radius, GameBoard& board) : width(width), height(height), radius(radius), board(board) {};

    size_t size() const;

    void enqueue(const ActionType action);
    void stepAndPrune();

    std::vector<BubbleData> getAllStepData() const;

protected:
    float width;
    float height;
    float radius;
    GameBoard& board;
    
    // NOTE: moved to list because of remove_if copy/move assignment issues with vector, try profiling
    std::list<ActionType> actions;
};

#endif