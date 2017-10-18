#pragma once


#include "common/SimpleMap.h"

#include <vector>


using std::vector;
using std::pair;


namespace game {

enum ActionType {
	ATTACK,
	DEAL_DAMAGE,
	DEATH,
	DRAW_CARD,
	PLAY_CARD,
	TURN_END,
	TURN_START,

	ACTION_TYPE_ITEMS,
};


enum ActionAttribute {
	COUNTERED,
	DRAW_FROM_EMPTY_DECK,
	TARGET,
	TARGET_PLAYER,
	AMOUNT,

	ACTION_ATTRIBUTE_ITEMS,
};


using ActionAttributeValue = int;


struct Action {
	Action(ActionType);

	ActionType type;
	SimpleMap<ActionAttribute, ActionAttributeValue> attributes;
};

}
