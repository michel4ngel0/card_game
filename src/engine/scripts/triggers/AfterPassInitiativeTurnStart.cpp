std::optional<Action> AfterPassInitiativeTurnStart(const Engine& engine, Action& action) {
    if (!action.is_type(EventType::PassInitiative) || !action.is_resolved())
        return std::optional<Action>();

    Action turn_start("Start the next turn", EventType::TurnStart);
    return std::optional<Action>(turn_start);
}
