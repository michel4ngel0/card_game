void PassInitiative(Engine& engine, SimpleMap<ActionAttribute, u32>& attributes) {
    engine.current_player += 1;
    engine.current_player %= engine.players.size();
}
