#include "action.hpp"

/* --- public --- */

void GameActionMgr::ActionType::step() {
    switch (effect) {
        case Effect::LAUNCH:
            {
                bubbleData[0].x += bubbleData[0].xVel;
                bubbleData[0].y += bubbleData[0].yVel;

                if (GameUtils::clamp(bubbleData[0].x, 0, parent.width - 2 * parent.radius))
                    bubbleData[0].xVel *= -1;
                if (GameUtils::clamp(bubbleData[0].y, 0, parent.height + 20.0f))
                    bubbleData[0].yVel *= -1;

                try {
                    const size_t row = GameUtils::yToRow(bubbleData[0].y, parent.radius);
                    const size_t col = GameUtils::xyToCol(bubbleData[0].x, bubbleData[0].y, parent.radius);

                    if (!GameUtils::usedLast(row, col))
                        pruneFlag = parent.board.update(row, col, bubbleData[0].hue);

                } catch (const std::out_of_range& e) {} // TODO: temporary, testing
            }
            break;

        case Effect::POP:
            break;

        case Effect::DROP:
            break;
    }
}

bool GameActionMgr::ActionType::shouldPrune() const {
    return std::all_of(bubbleData.begin(), bubbleData.end(), [this] (const BubbleData& bubble) {
        return bubble.x > parent.width or bubble.y > parent.height or bubble.x < 0 or bubble.y < 0;
    }) or pruneFlag;
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