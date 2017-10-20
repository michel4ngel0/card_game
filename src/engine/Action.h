#pragma once

#include <functional>
#include <optional>

#include "types.h"
#include <common/types.h>
#include <common/SimpleMap.h>

namespace game {

class Engine;

class Action {
public:
    Action(EventType type);
    Action(EventType type, std::function<void(Engine&)> script);
    void execute(Engine& engine);
    EventType get_type() const;

    SimpleMap<ActionAttribute, u32> attributes;

private:
    EventType type;
    std::function<void(Engine&)> script;
};

}