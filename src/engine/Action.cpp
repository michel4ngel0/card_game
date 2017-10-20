#include "Action.h"

namespace game {

Action::Action(std::string n, EventType t)
    : name(n), type(t), script(nullptr) {}

Action::Action(std::string n, EventType t, ActionScript s)
    : name(n), type(t), script(s) {}

void Action::execute(Engine& engine) {
    if (bool(script))
        script(engine, attributes);
}

bool Action::is_type(EventType t) const {
    if (type == EventType::None)
        return (type == EventType::None);
    return (t == type || t == EventType::Any || type == EventType::Any);
}

bool Action::is_resolved() const {
    return (attributes.get_or(ActionAttribute::Resolved, 0) == 1);
}

}