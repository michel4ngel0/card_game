#pragma once

namespace game {

enum class EventType {
    None,
    Any,

    GameStart,

    TurnStart,
    TurnEnd,
};

enum class TriggerWhen {
    Before,
    After,
};

enum class ActionAttribute {
    Countered,
};

enum class CardType {
    Minion,
    Spell,
};

enum class CardAttribute {
    Power,
    Toughness,
};

}