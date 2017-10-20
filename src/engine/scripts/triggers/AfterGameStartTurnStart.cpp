std::optional<Action> AfterGameStartTurnStart(const Engine& engine, Action& action) {
    if (!action.is_type(EventType::GameStart) || !action.is_resolved())
        return std::optional<Action>();

    Action turn_start("Start the very first turn", EventType::TurnStart);
    return std::optional<Action>(turn_start);
}
