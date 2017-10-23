#include "Engine.h"
#include "Action.h"
#include "Card.h"
#include "Trigger.h"
#include "ScriptLoader.h"
#include "Minion.h"

#include <stack>
#include <iostream>
#include <algorithm>

#include <common/types.h>

namespace game {

Engine::Engine() {
    bind_triggers();

    current_player = 0;

    players.resize(2);
    for (auto& player : players) {
        player.health = 20;
        player.fatigue_counter = 1;
    }

    Action start_game("Start the game", EventType::GameStart);
    handle_action(start_game);
}

void Engine::handle_action(Action action) {
    std::stack<std::pair<Action, bool>> stack;
    stack.push(std::make_pair(action, false));

    std::cout << "[incoming action] " << action.name.c_str() << std::endl;;

    while (!stack.empty()) {
        Action action = stack.top().first;

        if (!stack.top().second) {
            stack.top().second = true;
        } else {
            stack.pop();
            action.execute(*this);
            std::cout << "[resolved] " << action.name.c_str() << std::endl;
        }

        for (Action& triggered : collect_triggered(action))
            stack.push(std::make_pair(triggered, false));
    }
}

std::vector<Action> Engine::collect_triggered(Action action) {
    std::vector<Action> triggered_actions;
    
    for (auto& player : players)
        for (u32 id : player.board)
            for (auto& trigger : minions[id].triggers)
                trigger.check(*this, action, triggered_actions);

    for (auto& player : players)
        for (u32 id : player.hand)
            for (auto& trigger : cards[id].triggers)
                trigger.check(*this, action, triggered_actions);

    for (auto& player : players)
        for (u32 id : player.deck)
            for (auto& trigger : cards[id].triggers)
                trigger.check(*this, action, triggered_actions);

    for (auto& trigger : triggers)
        trigger.check(*this, action, triggered_actions);
    
    std::reverse(triggered_actions.begin(), triggered_actions.end());
    return triggered_actions;
}

void Engine::bind_triggers() {
    const ScriptLoader& s = ScriptLoader::get_instance();

    triggers.push_back(s.trigger("AfterGameStartTurnStart"));
    triggers.push_back(s.trigger("AfterTurnStartDrawCard"));
    triggers.push_back(s.trigger("AfterTurnEndStartNextTurn"));
    triggers.push_back(s.trigger("AfterDrawCardCheckForFatigue"));
}

}
