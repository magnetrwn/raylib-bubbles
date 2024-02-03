#include "action.hpp"

/* --- public --- */

bool GameActionMgr::isOngoing() const {
    return ongoing;
}

void GameActionMgr::step() {

}

void GameActionMgr::enqueue(const ActionType action) {
    actions.push_back(action);
}