#pragma once

#include <functional>
#include <map>

#include "types.h"

namespace game {

class ScriptLoader {
private:
    ScriptLoader();

public:
    static const ScriptLoader& get_instance();
    ActionScript action(std::string) const;
    TriggerScript trigger(std::string) const;

private:
    static ScriptLoader* the_singleton;

    std::map<std::string, ActionScript> actions;
    std::map<std::string, TriggerScript> triggers;
};

}