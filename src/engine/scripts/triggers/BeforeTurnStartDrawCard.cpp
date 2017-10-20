std::optional<Action> BeforeTurnStartDrawCard(const Engine& engine, Action& action) {
    if (!action.is_type(EventType::TurnStart) || action.is_resolved())
        return std::optional<Action>();

    ActionScript script = ScriptLoader::get_instance().action("DrawCardCurrentPlayer");
    Action draw_card("Draw a card", EventType::DrawCard, script);
    return std::optional<Action>(draw_card);
}
