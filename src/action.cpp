#include "action.hpp"

/* --- public --- */

void GameActionMgr::ActionType::step() {
    switch (effect) {
        case Effect::LAUNCH:
            {
                bubbleData[0].x += bubbleData[0].xVel;
                bubbleData[0].y += bubbleData[0].yVel;

                if (GameUtils::clamp(bubbleData[0].x, 0, parent.getWidth() - 2 * parent.getRadius()))
                    bubbleData[0].xVel *= -1;
                if (GameUtils::clamp(bubbleData[0].y, 0, parent.getHeight() + 20.0f))
                    bubbleData[0].yVel *= -1;
                break;
            }

        case Effect::POP:
            break;

        case Effect::DROP:
            break;
    }
}

bool GameActionMgr::ActionType::shouldPrune() const {
    return std::all_of(bubbleData.begin(), bubbleData.end(), [this] (const BubbleData& bubble) {
        return bubble.x > parent.getWidth() or bubble.y > parent.getHeight() or bubble.x < 0 or bubble.y < 0;
    }) or pruneFlag;
}

float GameActionMgr::getWidth() const {
    return width;
}

float GameActionMgr::getHeight() const {
    return height;
}

float GameActionMgr::getRadius() const {
    return radius;
}

size_t GameActionMgr::size() const {
    return actions.size();
}

void GameActionMgr::enqueue(const ActionType action) {
    actions.push_back(action);
}

void GameActionMgr::stepAndPrune() {
    for (ActionType& action : actions)
        action.step();

    actions.remove_if([] (const ActionType& action) {
        return action.shouldPrune();
    });
}

std::vector<GameActionMgr::BubbleData> GameActionMgr::getAllStepData() const {
    std::vector<BubbleData> all;

    for (const ActionType& action : actions)
        all.insert(all.end(), action.bubbleData.begin(), action.bubbleData.end());

    return all;
}