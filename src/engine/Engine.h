#pragma once

#include <vector>

#include "Action.h"
#include "types.h"

namespace game {

class Action;

class Engine {
public:
    void handle_action(Action action);

private:
    std::vector<Action> collect_triggered(Action action, TriggerWhen when);
};

}