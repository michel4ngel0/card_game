#pragma once

#include <functional>

#include <common/types.h>
#include <common/SimpleMap.h>

namespace game {

class Engine;
class Action;

enum class EventType {
    None,
    Any,

    GameStart,

    TurnStart,
    DrawCard,
    TurnEnd,
    PassInitiative,

    Damage,
};

enum class ActionAttribute {
    Resolved,

    Countered,

    DeckEmpty,

    TargetType,
    TargetId,

    Amount
};

enum class CardType {
    Minion,
    Spell,
};

enum class CardAttribute {
    Power,
    Toughness,
};

using ActionScript = std::function<void(Engine&, SimpleMap<ActionAttribute, u32>&)>;
using TriggerScript = std::function<void(const Engine&, Action&, std::vector<Action>&)>;

}