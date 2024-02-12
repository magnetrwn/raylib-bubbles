#include "action.hpp"

/* --- public --- */

void GameActionMgr::ActionType::step() {
    switch (effect) {
        case Effect::LAUNCH:
            break;
        case Effect::POP:
            break;
        case Effect::DROP:
            break;
    }
}

void GameActionMgr::enqueue(const ActionType action) {
    actions.push_back(action);
}

void GameActionMgr::stepAndPrune() {
    actions.erase(std::remove_if(actions.begin(), actions.end(), [this] (const ActionType& action) {
        return shouldPrune(action);
    }), actions.end());

    for (ActionType& action : actions)
        action.step();
}

/* --- protected --- */

bool GameActionMgr::shouldPrune(const ActionType& action) const {
    for (const auto& bubble : action.bubbleData)
        if (std::get<0>(bubble) <= width and std::get<1>(bubble) <= height)
            return false;

    return true;
}