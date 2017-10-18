#include "logic/GameLogic.h"
#include "logic/Action.h"

#include <iostream>
#include <chrono>


int main() {
    game::GameLogic engine;
    engine.start_new_game();

    auto time_then = std::chrono::high_resolution_clock::now();
    while (true) {
        auto time_now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> delta_t = time_now - time_then;
        if (delta_t.count() >= 1.0) {
            time_then = time_now;

            game::Action end_turn = game::Action(game::TURN_END);
            engine.handle_incoming_action(end_turn);
        }
    }
}
