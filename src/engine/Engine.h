#pragma once

#include <vector>
#include <map>

#include "Card.h"
#include "Minion.h"

#include "types.h"

namespace game {

class Action;
class Trigger;
class Loader;
class Permanent;

class Engine {
public:
    Engine();
    void handle_action(Action action);

private:
    std::vector<Action> collect_triggered(Action action);
    void bind_triggers();

public:
    struct Player {
        i32 health;
        i32 fatigue_counter;
        std::vector<u32> deck;
        std::vector<u32> hand;
        std::vector<u32> board;
    };
    std::vector<Player> players;
    u32 current_player;
    
    std::map<u32, Minion> minions;
    std::map<u32, Card> cards;
    
    std::vector<Trigger> triggers;
};

}