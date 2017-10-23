#pragma once

#include <vector>

#include "types.h"

namespace game {

class Trigger;

struct Minion {
    Minion();

    u32 power;
    u32 toughness;
    u32 damage_taken;
    std::vector<Trigger> triggers;
};

}
