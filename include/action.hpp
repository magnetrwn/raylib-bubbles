#ifndef ACTION_HPP_
#define ACTION_HPP_

#include <vector>
#include <algorithm>
#include <forward_list>
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

        bool pruneFlag;

        // NOTE: for sameAsLastRowCol()
        bool noLastRowCol;
        size_t lastRow;
        size_t lastCol;

        ActionType(const Effect effect, const std::vector<BubbleData>& bubbleData, const GameActionMgr& mgr)
            : effect(effect), parent(mgr), bubbleData(bubbleData), pruneFlag(false), noLastRowCol(true) {};

        void step();

        bool shouldPrune() const;
        bool sameAsLastRowCol(const size_t row, const size_t col);
    };

    GameActionMgr(const float width, const float height, const float radius, GameBoard& board)
        : width(width), height(height), radius(radius), board(board) {};

    size_t size() const;

    void enqueue(const ActionType action);
    void stepAndPrune();

    std::vector<BubbleData> getAllStepData() const;

protected:
    const float width;
    const float height;
    const float radius;
    GameBoard& board;
    
    // NOTE: moved to forward_list because of remove_if copy/move assignment issues with vector, try profiling
    std::forward_list<ActionType> actions;
};

#endif