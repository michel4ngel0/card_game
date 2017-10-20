#pragma once

#include "types.h"

#include "Trigger.h"
#include <common/types.h>
#include <common/SimpleMap.h>

namespace game {

class Trigger;

struct Card {
    // Card(const CardTemplate& template);

    CardType type;
    SimpleMap<CardAttribute, u32> attributes;
    std::vector<Trigger> triggers;
};

}