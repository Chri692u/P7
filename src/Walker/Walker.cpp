#include "Walker.hpp"


Path Walker::Walk(BaseHeuristic *heuristic, BaseDepthFunction *depthFunc, const PDDLState *state) {
    const int depth = depthFunc->GetDepth();
    std::vector<PDDLActionInstance> steps; steps.reserve(depth);
    std::unordered_set<PDDLState> visitedStates; visitedStates.reserve(depth);

    PDDLState tempState = PDDLState(state->unaryFacts, state->multiFacts);
    for (int i = 0; i < depth; i++) {
        std::vector<PDDLActionInstance> possibleActions;
        possibleActions = actionGenerator.GenerateActions(&tempState);

        if (possibleActions.size() == 0) break;
        PDDLActionInstance *chosenAction = heuristic->NextChoice(&tempState, &possibleActions);
        tempState.DoAction(chosenAction);

        if (visitedStates.contains(tempState))
            break;
        else {
            visitedStates.emplace(tempState);
            steps.push_back(*chosenAction);

            if (config->GetBool("printwalkersteps")) {
                std::string stateinfo = tempState.ToString(this->instance);
                std::string actioninfo = chosenAction->ToString(this->instance);
                std::string content = "echo '" + stateinfo + "\n" + actioninfo + "'" + " >> walkerLog";

                system(content.c_str());
            }
        }
    }

    return Path(steps);
}

std::vector<Path> Walker::Walk(BaseHeuristic *heuristic, BaseDepthFunction *depthFunc, BaseWidthFunction *widthFunc) {
    if (config->GetBool("printwalkersteps")) {
        std::string command = "truncate -s 0 walkerLog";
        system(command.c_str());
    }

    ProgressBarHelper* bar;
	if (config->GetBool("debugmode"))
		bar = new ProgressBarHelper(widthFunc->max, "Walking", 1);

    std::vector<Path> paths;
    unsigned int current;
    while (widthFunc->Iterate(&current)) {
        Path path = Walk(heuristic, depthFunc, &this->instance->problem->initState);
        paths.push_back(path);

        if (config->GetBool("debugmode"))
            bar->SetTo(current);
    }
    if (config->GetBool("debugmode"))
        bar->End();
    return paths;
}
