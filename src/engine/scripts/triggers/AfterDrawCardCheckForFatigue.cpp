void AfterDrawCardCheckForFatigue(const Engine& engine, Action& action, std::vector<Action>& queue) {
    if (!action.is_type(EventType::DrawCard) || !action.is_resolved())
        return;

    if (action.attributes.get_or(ActionAttribute::DeckEmpty, 0) == 0)
        return;

    u32 player = action.attributes.get_or(ActionAttribute::TargetId, -1);
    if (player == -1)
        throw script_runtime_error("Incorrect player id");

    u32 amount = engine.players[player].fatigue_counter;

    ActionScript damage_script = ScriptLoader::get_instance().action("DealDamageToPlayer");
    Action deal_fatigue_dmg("Deal fatigue damage to player " + std::to_string(player),
                            EventType::Damage, damage_script);
    deal_fatigue_dmg.attributes.set(ActionAttribute::TargetId, player);
    deal_fatigue_dmg.attributes.set(ActionAttribute::Amount, amount);
    queue.push_back(deal_fatigue_dmg);

    ActionScript increment_script = ScriptLoader::get_instance().action("IncrementFatigueCounter");
    Action increment_fatigue_counter("Increase fatigue counter for player " + std::to_string(player),
                                     EventType::None, increment_script);
    increment_fatigue_counter.attributes.set(ActionAttribute::TargetId, player);
    queue.push_back(increment_fatigue_counter);
}