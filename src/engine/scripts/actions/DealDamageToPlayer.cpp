void DealDamageToPlayer(Engine& engine, SimpleMap<ActionAttribute, u32>& attributes) {
    u32 player_id = attributes.get_or(ActionAttribute::TargetId, -1);
    if (player_id < 0 || player_id >= engine.players.size())
        throw script_runtime_error("Incorrect player id: " + std::to_string(player_id));

    auto amount = attributes.get(ActionAttribute::Amount);
    if (!amount)
        throw script_runtime_error("Amount of damage not specified");

    engine.players[player_id].health -= amount.value();
}
