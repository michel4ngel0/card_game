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
    std::optional<Action> check(const Engine& engine, Action& action) const;

private:
    TriggerScript generate_action;
};

}