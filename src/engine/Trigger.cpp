#include "Trigger.h"

#include "Action.h"

namespace game {

Trigger::Trigger(EventType et, TriggerWhen w,
                 std::function<bool(const Engine&, const Action&)> cc,
                 std::function<Action(const Engine&, Action&)> ga) :
    event_type(et), when(w), check_conditions(cc), generate_action(ga) {
}

EventType Trigger::get_event_type() const {
    return event_type;
}

TriggerWhen Trigger::get_when() const {
    return when;
}

std::optional<Action> Trigger::check_trigger(const Engine& engine, Action& a) const {
    if (bool(check_conditions) && check_conditions(engine, a))
        return std::optional<Action>(generate_action(engine, a));
    else
        return std::optional<Action>();
}

}