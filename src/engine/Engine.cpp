#include "Engine.h"
#include "Action.h"
#include "Card.h"
#include "Trigger.h"
#include "ScriptLoader.h"

#include <stack>
#include <iostream>

#include <common/types.h>

namespace game {

Engine::Engine() {
    bind_triggers();

    current_player = 0;

    players.resize(2);

    Action start_game("Start the game", EventType::GameStart);
    handle_action(start_game);
}

void Engine::handle_action(Action action) {
    std::stack<Action> stack;
    stack.push(action);

    std::cout << "[incoming action] " << action.name.c_str() << std::endl;

    while (!stack.empty()) {
        Action action = stack.top();

        if (!action.is_resolved()) {
            stack.top().attributes.set(ActionAttribute::Resolved, 1);

            for (Action& triggered : collect_triggered(action))
                stack.push(triggered);
        } else {
            stack.pop();
            action.execute(*this);
            std::cout << "[resolved] " << action.name.c_str() << std::endl;

            for (Action& triggered : collect_triggered(action))
                stack.push(triggered);
        }
    }
}

std::vector<Action> Engine::collect_triggered(Action action) {
    std::vector<Action> triggered_actions;
    for (auto& trigger : triggers) {
        std::optional<Action> maybe_action = trigger.check(*this, action);
        if (maybe_action.has_value())
            triggered_actions.push_back(maybe_action.value());
    }
    return triggered_actions;
}

void Engine::bind_triggers() {
    const ScriptLoader& s = ScriptLoader::get_instance();

    triggers.push_back(s.trigger("AfterGameStartTurnStart"));
    triggers.push_back(s.trigger("BeforeTurnStartDrawCard"));
    triggers.push_back(s.trigger("AfterTurnEndPassInitiative"));
    triggers.push_back(s.trigger("AfterPassInitiativeTurnStart"));
}

}
