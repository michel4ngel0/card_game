#include "GamePiece.h"


#include <iostream>

namespace game {

GamePiece::GamePiece(piece_id my_id) {
    id = my_id;
}

const char* GamePiece::description() {
    return "generic game piece";
}

void GamePiece::register_triggers(GameLogic& logic) {}

}