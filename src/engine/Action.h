#pragma once

#include <functional>

#include "Engine.h"
#include "types.h"

namespace game {

class Engine;

class Action {
public:
    Action(EventType type, std::function<void(Engine&)> script);
    void execute(Engine& engine);

private:
    EventType type;
    std::function<void(Engine&)> script;
};

}