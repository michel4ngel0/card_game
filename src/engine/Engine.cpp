#include "Engine.h"

#include <stack>

#include "common/types.h"

namespace game {

void Engine::handle_action(Action action) {
    std::stack<std::pair<Action, TriggerWhen>> stack;
    stack.push(std::make_pair(action, TriggerWhen::Before));

    while (!stack.empty()) {
        Action action = stack.top().first;
        TriggerWhen status = stack.top().second;

        if (status == TriggerWhen::Before) {
            stack.top().second = TriggerWhen::After;

            for (Action& triggered : collect_triggered(action, TriggerWhen::Before))
                stack.push(std::make_pair(triggered, TriggerWhen::Before));
        } else {
            action.execute(*this);
            stack.pop();

            for (Action& triggered : collect_triggered(action, TriggerWhen::After))
                stack.push(std::make_pair(triggered, TriggerWhen::Before));
        }
    }
}

std::vector<Action> Engine::collect_triggered(Action action, TriggerWhen when) {
    return std::vector<Action>();
}

}
