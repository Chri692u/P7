#include "Walker.hpp"

Path Walker::Walk() {
    return Walk(instance->problem->initState);
}

Path Walker::Walk(PDDLState state) {
    int depth = depthFunc->GetDepth();
    Path path = Path();
    for (int i = 0; i < depth; i++) {
        auto actions = actionGenerator.GenerateActions(&state);
        // Should this be handled?
        if (actions.size() == 0)
            break;
        auto chosenAction = heuristic->NextChoice(actions);
        path.AddStep(chosenAction);
        state = DoAction(state, heuristic->NextChoice(actions));
    }
    return path;
}

PDDLState Walker::DoAction(PDDLState state, PDDLActionInstance action) {
    // For each action effect, change the state accordingly
    for (int i = 0; i < action.action.effects.size(); i++) {
        auto effect = action.action.effects[i];
        state.Update(&action.action, effect, action.arguments);
    }
    
    return state;
}
