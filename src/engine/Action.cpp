#include "Action.h"

namespace game {

Action::Action(EventType t)
    : type(t), script(nullptr) {}

Action::Action(EventType t, std::function<void(Engine&)> s)
    : type(t), script(s) {}

void Action::execute(Engine& engine) {
    if (bool(script))
        script(engine);
}

EventType Action::get_type() const {
    return type;
}

}
