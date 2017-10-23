void DrawCard(Engine& engine, SimpleMap<ActionAttribute, u32>& attributes) {
    u32 player_id = attributes.get_or(ActionAttribute::TargetId, -1);
    if (player_id < 0 || player_id >= engine.players.size())
        throw script_runtime_error("Incorrect player id: " + std::to_string(player_id));

    auto& deck = engine.players[player_id].deck;
    auto& hand = engine.players[player_id].hand;

    if (deck.empty()) {
        attributes.set(ActionAttribute::DeckEmpty, 1);
    } else {
        auto top_card = deck.back();
        deck.pop_back();
        hand.push_back(top_card);
    }
}
