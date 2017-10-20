#include "Trigger.h"

#include "Action.h"

namespace game {

Trigger::Trigger(TriggerScript ga) :
    generate_action(ga) {
}

std::optional<Action> Trigger::check(const Engine& engine, Action& a) const {
    return generate_action(engine, a);
}

}