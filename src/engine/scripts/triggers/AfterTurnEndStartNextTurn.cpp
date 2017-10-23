void AfterTurnEndStartNextTurn(const Engine& engine, Action& action, std::vector<Action>& queue) {
    if (!action.is_type(EventType::TurnEnd) || !action.is_resolved())
        return;

    ActionScript script = ScriptLoader::get_instance().action("PassInitiative");
    Action pass_initiative("Pass initiative to the next player", EventType::PassInitiative, script);
    queue.push_back(pass_initiative);

    Action turn_start("Start the next turn", EventType::TurnStart);
    queue.push_back(turn_start);
}
