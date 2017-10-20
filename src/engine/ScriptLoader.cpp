#include "ScriptLoader.h"

#include <exception>
#include <functional>
#include <iostream>

#include "Engine.h"
#include "types.h"

#include "Action.h"

#define REGISTER_ACTION(name) \
    actions.insert(std::make_pair(#name, name))

#define REGISTER_TRIGGER(name) \
    triggers.insert(std::make_pair(#name, name))

namespace {
    class missing_script : std::exception {
    public:
        missing_script(std::string function_name) {
            info = std::string("Script \"") + function_name + "\" not found";
        }
        const char* what() const {
            return info.c_str();
        }
    private:
        std::string info;
    };
}

namespace game {

#include "scripts/actions/DrawCardCurrentPlayer.cpp"
#include "scripts/actions/PassInitiative.cpp"

#include "scripts/triggers/AfterGameStartTurnStart.cpp"
#include "scripts/triggers/AfterPassInitiativeTurnStart.cpp"
#include "scripts/triggers/AfterTurnEndPassInitiative.cpp"
#include "scripts/triggers/BeforeTurnStartDrawCard.cpp"

ScriptLoader* ScriptLoader::the_singleton = nullptr;

ScriptLoader::ScriptLoader() {

    REGISTER_ACTION(DrawCardCurrentPlayer);
    REGISTER_ACTION(PassInitiative);

    REGISTER_TRIGGER(AfterGameStartTurnStart);
    REGISTER_TRIGGER(AfterPassInitiativeTurnStart);
    REGISTER_TRIGGER(AfterTurnEndPassInitiative);
    REGISTER_TRIGGER(BeforeTurnStartDrawCard);

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
