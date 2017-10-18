#pragma once

#include "common/SimpleMap.h"


namespace game {

class GameLogic;
class Action;

using Trigger = void (*) (GameLogic&, Action&);
using piece_id = int;


enum PieceAttribute {
	IS_HERO,

	TOUGHNESS,
	POWER,
	DAMAGE_TAKEN,
	MANA_COST,

	PIECE_ATTRIBUTE_ITEMS,
};


using PieceAttributeValue = int;


struct GamePiece {
	GamePiece(piece_id);
	virtual const char* description();
	virtual void register_triggers(GameLogic&);

	piece_id id;
	SimpleMap<PieceAttribute, PieceAttributeValue> attributes;
};

}
