#include "Action.h"

namespace game {

Action::Action(EventType t, std::function<void(Engine&)> s)
    : type(t), script(s) {}

void Action::execute(Engine& engine) {
    if (script.target<void(Engine&)>() != nullptr)
        script(engine);
} 

}
