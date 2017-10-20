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
    Action(std::string, EventType type);
    Action(std::string, EventType type, ActionScript script);
    void execute(Engine& engine);
    bool is_type(EventType type) const;
    bool is_resolved() const;

    std::string name;
    SimpleMap<ActionAttribute, u32> attributes;

private:
    EventType type;
    ActionScript script;
};

}