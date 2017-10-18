#include "GameLogic.h"
#include "Action.h"

#include <stack>
#include <iostream>
#include <algorithm>
#include <exception>


using std::pair;
using std::make_pair;
using std::stack;


namespace game {

//  Game rules
void rule_start_next_turn(GameLogic& logic, Action&) {
    Action turn_start = Action(TURN_START);
    logic.queue_action(turn_start);
}

void rule_draw_on_turn_start(GameLogic& logic, Action&) {
    Action draw_card = Action(DRAW_CARD);
    draw_card.attributes.set(TARGET_PLAYER, logic.current_player);
    logic.queue_action(draw_card);
}

void rule_check_for_fatigue(GameLogic& logic, Action& action) {
    int player_id = action.attributes.get_or(TARGET_PLAYER, -1);

    if (player_id == -1)
        throw std::logic_error("Draw action without player id set");

    if (action.attributes.get_or(DRAW_FROM_EMPTY_DECK, 0)) {
        Action fatigue = Action(DEAL_DAMAGE);
        fatigue.attributes.set(TARGET, logic.players[player_id].hero);
        fatigue.attributes.set(AMOUNT, 2);
        logic.queue_action(fatigue);
    }
}

struct GameRulesAura : public GamePiece {
    GameRulesAura(piece_id my_id) : GamePiece(my_id) {}
    virtual const char* description() {
        return "aura enforcing rules of the game";
    }
    
    virtual void register_triggers(GameLogic& logic) {
        logic.register_succeeding_trigger(TURN_END, rule_start_next_turn, id);
        logic.register_succeeding_trigger(TURN_START, rule_draw_on_turn_start, id);

        logic.register_succeeding_trigger(DRAW_CARD, rule_check_for_fatigue, id);

        std::cout << "registered the gamerules triggers!" << std::endl;
    }
};

piece_id GameLogic::get_next_id() {
    return next_id++;
}

void GameLogic::queue_action(Action& action) {
    action_stack.push(make_pair(action, false));
}

void GameLogic::start_new_game() {
    next_id = 0;

    {
        piece_id id = get_next_id();
        GamePiece* rules_aura = new GameRulesAura(id);
        rules_aura->register_triggers(*this);
        pieces.insert(make_pair(id, rules_aura));
    }

    for (Player& player: players) {
        piece_id hero_id = get_next_id();
        pieces.insert(make_pair(hero_id, new GamePiece(hero_id)));
        player.hero = hero_id;

        for (int i = 0; i < 5; ++i) {
            piece_id id = get_next_id();
            pieces.insert(make_pair(id, new GamePiece(id)));
            player.deck.push_back(id);
        }
        std::random_shuffle(player.deck.begin(), player.deck.end());
    }
    
    current_player = 0;
}

// void GameLogic::get_available_actions() {}

void GameLogic::handle_incoming_action(Action incoming_action) {
    if (!action_stack.empty())
        throw std::logic_error("Can't handle the action, stack is not empty");
    queue_action(incoming_action);

    std::cout << "[incoming action] " << int(incoming_action.type) << std::endl;;

    while (!action_stack.empty()) {
        auto [action, traversed] = action_stack.top();

        if (!traversed) {
            action_stack.top().second = true;

            for (auto& [id, trigger] : preceding_triggers[action.type])
                trigger(*this, action);
        } else {
            action_stack.pop();

            if (action.attributes.get_or(COUNTERED, 0) != 1) {
                resolve_action(action);

                for (int i = 0; i < 2; ++i) {
                    GamePiece* hero = pieces[players[i].hero];
                    int hero_toughness = hero->attributes.get_or(TOUGHNESS, 0);
                    int hero_damage = hero->attributes.get_or(DAMAGE_TAKEN, 0);
                    
                    std::cout << "damage taken by player " << i << ": ";
                    std::cout << hero->attributes.get_or(DAMAGE_TAKEN, 0);
                    std::cout << std::endl;

                    if (hero_damage >= hero_toughness) {
                        //  end the game
                        //  ...
                    }
                }

                for (auto& [id, trigger]: succeeding_triggers[action.type])
                    trigger(*this, action);
            }
        }
    }
}

void GameLogic::resolve_action(Action& action) {
    std::cout << "[resolving action] " << int(action.type) << std::endl;

    auto& attrs = action.attributes;

    switch (action.type) {
        case ATTACK: {
            break;
        }
        case DEAL_DAMAGE: {
            piece_id target_id = attrs.get_or(TARGET, -1);
            int amount = attrs.get_or(AMOUNT, 0);
            
            if (target_id == -1)
                throw std::logic_error("Damage action with no target");

            GamePiece* target = pieces[target_id];

            int damage_taken = target->attributes.get_or(DAMAGE_TAKEN, 0);
            target->attributes.set(DAMAGE_TAKEN, damage_taken + amount);

            //  check for death
            //  ...

            break;
        }
        case DEATH: {
            break;
        }
        case DRAW_CARD: {
            auto& player = players[current_player];

            if (!player.deck.empty()) {
                piece_id id = player.deck.back();
                player.deck.pop_back();
                player.hand.push_back(id);
            } else {
                attrs.set(DRAW_FROM_EMPTY_DECK, 1);
            }

            break;
        }
        case PLAY_CARD: {
            break;
        }
        case TURN_END: {
            break;
        }
        case TURN_START: {
            current_player = (current_player + 1) % 2;
            break;
        }
        default:
            throw std::logic_error("Unhandled action type");
    }

    history.push_back(action);
}

void GameLogic::register_preceding_trigger(ActionType type,
                                           Trigger trigger,
                                           piece_id id) {
    preceding_triggers[type].push_back(make_pair(id, trigger));
}

void GameLogic::register_succeeding_trigger(ActionType type,
                                            Trigger trigger,
                                            piece_id id) {
    succeeding_triggers[type].push_back(make_pair(id, trigger));
}

}
