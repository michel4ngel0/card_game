#include "Engine.h"
#include "Action.h"
#include "Card.h"
#include "Trigger.h"

#include <stack>
#include <iostream>

#include <common/types.h>

namespace game {

Engine::Engine() {
    Action start_game(EventType::GameStart);
    handle_action(start_game);
}

void Engine::handle_action(Action action) {
    std::stack<std::pair<Action, TriggerWhen>> stack;
    stack.push(std::make_pair(action, TriggerWhen::Before));

    std::cout << "I'm handling an action " << int(action.get_type()) << std::endl;

    while (!stack.empty()) {
        Action action = stack.top().first;
        TriggerWhen status = stack.top().second;

        if (status == TriggerWhen::Before) {
            stack.top().second = TriggerWhen::After;

            for (Action& triggered : collect_triggered(action, TriggerWhen::Before))
                stack.push(std::make_pair(triggered, TriggerWhen::Before));
        } else {
            stack.pop();
            action.execute(*this);

            for (Action& triggered : collect_triggered(action, TriggerWhen::After))
                stack.push(std::make_pair(triggered, TriggerWhen::Before));
        }
    }
}

std::vector<Action> Engine::collect_triggered(Action action, TriggerWhen when) {
    return std::vector<Action>();
}

}
