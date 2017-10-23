void AfterTurnStartDrawCard(const Engine& engine, Action& action, std::vector<Action>& queue) {
    if (!action.is_type(EventType::TurnStart) || !action.is_resolved())
        return;

    ActionScript script = ScriptLoader::get_instance().action("DrawCard");
    Action draw_card("Draw a card", EventType::DrawCard, script);
    draw_card.attributes.set(ActionAttribute::TargetId, engine.current_player);
    queue.push_back(draw_card);
}
