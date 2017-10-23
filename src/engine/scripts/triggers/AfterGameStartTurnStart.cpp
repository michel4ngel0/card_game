void AfterGameStartTurnStart(const Engine& engine, Action& action, std::vector<Action>& queue) {
    if (!action.is_type(EventType::GameStart) || !action.is_resolved())
        return;

    Action turn_start("Start the very first turn", EventType::TurnStart);
    queue.push_back(turn_start);
}
