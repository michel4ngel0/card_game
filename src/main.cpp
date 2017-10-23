#include <iostream>
#include <chrono>

#include "engine/Engine.h"
#include "engine/Action.h"

int main() {
    game::Engine engine;

    auto time_then = std::chrono::high_resolution_clock::now();
    while (true) {
        auto time_now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> delta_t = time_now - time_then;
        if (delta_t.count() >= 5.0) {
            time_then = time_now;

            game::Action end_turn("End the turn", game::EventType::TurnEnd);
            engine.handle_action(end_turn);
        }
    }
}
