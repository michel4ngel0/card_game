#pragma once

#include "Action.h"
#include "GamePiece.h"

#include <vector>
#include <map>
#include <stack>


using std::array;
using std::map;
using std::vector;
using std::stack;


namespace game {

using Zone = vector<piece_id>;

struct Player {
    piece_id hero;
    Zone deck;
    Zone hand;
    // Zone board;
    // Zone graveyard;
};


class GameLogic {
public:
    void start_new_game();
    // void get_available_actions();
    void handle_incoming_action(Action);
    void queue_action(Action&);
    void resolve_action(Action&);

    void register_preceding_trigger(ActionType, Trigger, piece_id);
    void register_succeeding_trigger(ActionType, Trigger, piece_id);

    piece_id get_next_id();
    
    array<Player, 2> players;
    map<piece_id, GamePiece*> pieces;
    uint8_t current_player;
    vector<Action> history;

private:
    piece_id next_id;
    stack<pair<Action, bool>> action_stack;
    array<vector<pair<piece_id, Trigger>>, ACTION_TYPE_ITEMS> preceding_triggers;
    array<vector<pair<piece_id, Trigger>>, ACTION_TYPE_ITEMS> succeeding_triggers;
};

}