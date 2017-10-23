#include "ScriptLoader.h"

#include <exception>
#include <functional>
#include <iostream>
#include <string>

#include "Engine.h"
#include "types.h"

#include "Action.h"

#define REGISTER_ACTION(name) \
    actions.insert(std::make_pair(#name, name))

#define REGISTER_TRIGGER(name) \
    triggers.insert(std::make_pair(#name, name))

namespace {
    class custom_exception : std::exception {
    public:
        const char* what() const {
            return info.c_str();
        }
    protected:
        std::string info;
    };

    class missing_script : public custom_exception {
    public:
        missing_script(std::string function_name) {
            info = std::string("Script \"") + function_name + "\" not found";
            std::cerr << info << std::endl;
        }
    };

    class script_runtime_error : public custom_exception {
    public:
        script_runtime_error(std::string error_info) {
            info = error_info;
            std::cerr << info << std::endl;
        }
    };
}

namespace game {

#include "scripts/actions/DrawCard.cpp"
#include "scripts/actions/PassInitiative.cpp"
#include "scripts/actions/DealDamageToPlayer.cpp"
#include "scripts/actions/IncrementFatigueCounter.cpp"

#include "scripts/triggers/AfterGameStartTurnStart.cpp"
#include "scripts/triggers/AfterTurnEndStartNextTurn.cpp"
#include "scripts/triggers/AfterTurnStartDrawCard.cpp"
#include "scripts/triggers/AfterDrawCardCheckForFatigue.cpp"

ScriptLoader* ScriptLoader::the_singleton = nullptr;

ScriptLoader::ScriptLoader() {

    REGISTER_ACTION(DrawCard);
    REGISTER_ACTION(PassInitiative);
    REGISTER_ACTION(DealDamageToPlayer);
    REGISTER_ACTION(IncrementFatigueCounter);

    REGISTER_TRIGGER(AfterGameStartTurnStart);
    REGISTER_TRIGGER(AfterTurnEndStartNextTurn);
    REGISTER_TRIGGER(AfterTurnStartDrawCard);
    REGISTER_TRIGGER(AfterDrawCardCheckForFatigue);
}

const ScriptLoader& ScriptLoader::get_instance() {
    if (ScriptLoader::the_singleton == nullptr)
        ScriptLoader::the_singleton = new ScriptLoader();

    return *the_singleton;
}

ActionScript ScriptLoader::action(std::string name) const {
    auto record = actions.find(name);
    if (record == actions.end())
        throw ::missing_script(name);
    else
        return ActionScript(record->second);
}

TriggerScript ScriptLoader::trigger(std::string name) const {
    auto record = triggers.find(name);
    if (record == triggers.end())
        throw ::missing_script(name);
    else
        return TriggerScript(record->second);
}

}
