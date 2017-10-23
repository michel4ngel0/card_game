#include "Trigger.h"

#include "Action.h"

namespace game {

Trigger::Trigger(TriggerScript ga) :
    generate_action(ga) {
}

void Trigger::check(const Engine& engine, Action& a, std::vector<Action>& q) const {
    return generate_action(engine, a, q);
}

}