#pragma once

#include <vector>
#include <map>

#include "Card.h"

#include "types.h"
#include <common/types.h>

namespace game {

class Action;
class Trigger;
class Loader;

class Engine {
public:
    Engine();
    void handle_action(Action action);

private:
    std::vector<Action> collect_triggered(Action action);
    void bind_triggers();

public:
    struct Player {
        std::vector<u32> deck;
        std::vector<u32> hand;
    };
    std::vector<Player> players;
    std::map<u32, Card> cards;
    std::vector<Trigger> triggers;
    u32 current_player;
};

}