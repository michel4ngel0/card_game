#pragma once

#include <functional>
#include <optional>

#include "types.h"

namespace game {

class Action;
class Engine;

class Trigger {
public:
    Trigger(EventType type, TriggerWhen when,
            std::function<bool(const Engine&, const Action&)> check_conditions,
            std::function<Action(const Engine&, Action&)> generate_action);
    EventType get_event_type() const;
    TriggerWhen get_when() const;
    std::optional<Action> check_trigger(const Engine& engine, Action& action) const;

private:
    EventType event_type;
    TriggerWhen when;
    std::function<bool(const Engine&, const Action&)> check_conditions;
    std::function<Action(const Engine&, Action&)> generate_action;
};

}