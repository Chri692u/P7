#include "ActionGenerator.hpp"

std::vector<PDDLActionInstance> ActionGenerator::GenerateActions(PDDLState *state) {
    std::vector<PDDLAction> domainActions = domain->actions;
    std::vector<PDDLActionInstance> legalActions;
    for (const auto& action : domainActions) {
        auto tempActions = GenerateLegal(action, state);
        for (const auto& tempAction : tempActions)
            legalActions.push_back(tempAction);
    }
    return legalActions;
}

std::vector<PDDLActionInstance> ActionGenerator::GenerateLegal(PDDLAction action, PDDLState *state) {
    std::vector<PDDLActionInstance> legalActions;
    int parameterCount = action.parameters.size();
    PDDLArg *parameters[parameterCount];
    for (int i = 0; i < parameterCount; i++)
        parameters[i] = &action.parameters[i];
    std::vector<PDDLLiteral> parameterLiterals[parameterCount];
    for (int i = 0; i < parameterCount; i++)
        parameterLiterals[i] = GetPreconditions(action, parameters[i]);
    std::vector<PDDLLiteral> unaryLiterals[parameterCount];
    std::vector<PDDLLiteral> multiLiterals[parameterCount];
    for (int i = 0; i < parameterCount; i++)
        SplitLiterals(parameterLiterals[i], &unaryLiterals[i], &multiLiterals[i]);

    std::vector<std::string> candidateObjects[parameterCount];
    for (int i = 0; i < parameterCount; i++)
        candidateObjects[i] = GetCandidateObjects(&action, state, unaryLiterals[i]);
    
    // if some parameter doesn't have any candidate object, the action is not possible
    for (int i = 0; i < parameterCount; i++)
        if (candidateObjects[i].size() == 0)
            return legalActions;

    std::vector<int> indexes(parameterCount, 0);
    do {
        std::vector<std::string> objects;
        for (int i = 0; i < parameterCount; i++) 
            objects.push_back(candidateObjects[i][indexes[i]]);
        // test whether any multi literals do not match these objects
        bool legalAction = true;
        for (int i = 0; i < parameterCount; i++) {
            for (auto literal : multiLiterals[i]) {
                if (!state->IsMultiLiteralTrue(&action, literal, objects)) {
                    legalAction = false;
                    break;
                }  
            }
            if (!legalAction)
                break;
        }
        if (legalAction)
                legalActions.push_back(PDDLActionInstance(action, objects));
        
    } while (Increment(&indexes, candidateObjects));

    return legalActions;
}

std::vector<PDDLLiteral> ActionGenerator::GetPreconditions(PDDLAction action, PDDLArg *param) {
    std::vector<PDDLLiteral> preconditions;
    for (auto precondition : action.preconditions)
        for (auto arg : precondition.predicate.args)
            if (arg.name == param->name) {
                preconditions.push_back(precondition);
                break;
            }
    return preconditions;
}

std::vector<std::string> ActionGenerator::GetCandidateObjects(PDDLAction* action, PDDLState *state, std::vector<PDDLLiteral> preconditions) {
    std::vector<std::string> candidateObjects;
    for (const auto& object : *state->objects) {
        bool validObject = true;
        for (const auto& precondition : preconditions) {
            if (!state->IsUnaryLiteralTrue(action, precondition, object)) {
                validObject = false;
                break;
            }
        }  
        if (validObject)
            candidateObjects.push_back(object);
    }
    return candidateObjects;    
}

void ActionGenerator::SplitLiterals(std::vector<PDDLLiteral> literals, std::vector<PDDLLiteral> *unaryLiterals, std::vector<PDDLLiteral> *multiLiterals) {
    for (auto literal : literals)
        if (literal.predicate.args.size() > 1)
            (*multiLiterals).push_back(literal);
        else
            (*unaryLiterals).push_back(literal);
}

bool ActionGenerator::Increment(std::vector<int> *indexes, std::vector<std::string> objects[]) {
    int incrementIndex = -1;
    for (int i = 0; i < indexes->size(); i++) {
        if ((*indexes)[i] + 1 < objects[i].size()) {
            (*indexes)[i]++;
            incrementIndex = i;
            break;
        }
    }
    for (int i = 0; i < incrementIndex; i++)
        (*indexes)[i] = 0;
    return (incrementIndex != -1);
}
