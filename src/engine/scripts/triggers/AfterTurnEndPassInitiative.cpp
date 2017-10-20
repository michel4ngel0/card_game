std::optional<Action> AfterTurnEndPassInitiative(const Engine& engine, Action& action) {
    if (!action.is_type(EventType::TurnEnd) || !action.is_resolved())
        return std::optional<Action>();

    ActionScript script = ScriptLoader::get_instance().action("PassInitiative");
    Action pass_initiative("Pass initiative to the next player", EventType::PassInitiative, script);
    return std::optional<Action>(pass_initiative);
}
