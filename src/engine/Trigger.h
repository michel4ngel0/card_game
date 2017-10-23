#pragma once

#include <functional>
#include <optional>

#include "types.h"

namespace game {

class Action;
class Engine;

class Trigger {
public:
    Trigger(TriggerScript generate_action);
    void check(const Engine& engine, Action& action, std::vector<Action>& queue) const;

private:
    TriggerScript generate_action;
};

}