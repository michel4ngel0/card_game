void DrawCardCurrentPlayer(Engine& engine, SimpleMap<ActionAttribute, u32>& attributes) {
    auto& deck = engine.players[engine.current_player].deck;
    auto& hand = engine.players[engine.current_player].hand;

    if (deck.empty()) {
        attributes.set(ActionAttribute::DeckEmpty, 1);
    } else {
        auto top_card = deck.back();
        deck.pop_back();
        hand.push_back(top_card);
    }
}
