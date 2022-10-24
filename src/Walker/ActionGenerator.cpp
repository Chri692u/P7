#include "ActionGenerator.hpp"

using namespace std;

vector<PDDLActionInstance> ActionGenerator::GenerateActions(const PDDLState *state) const {
    vector<PDDLActionInstance> legalActions;
    const int domainLength = domain->actions.size();
    for (int i = 0; i < domainLength; i++) {
        vector<PDDLActionInstance> tempActions = GenerateActions(&(domain->actions[i]), state);
        copy(tempActions.begin(), tempActions.end(), back_inserter(legalActions));
    }
    return legalActions;
}

vector<PDDLActionInstance> ActionGenerator::GenerateActions(const PDDLAction *action, const PDDLState *state) const {
    vector<PDDLActionInstance> legalActions;

    // Object which fulfill the unary literals of the action preconditions
    vector<unordered_set<unsigned int>> candidateObjects;
    candidateObjects.reserve(action->parameters.size());
    if (!GetCandidateObjects(candidateObjects, action, state))
        return legalActions;
    

    vector<unordered_set<unsigned int>::iterator> iteration;
    const int candidateObjectsLength = candidateObjects.size();
    iteration.reserve(candidateObjectsLength);
    for (int i = 0; i < candidateObjectsLength; i++)
        iteration.push_back(candidateObjects[i].begin());

    // Iterate over each pairing of candidate objects
    // Then remove those that do not match non-unary preconditions
    // Those that match all are added as a legal action
    const int iterationSize = iteration.size();
    do {
        vector<unsigned int> objects;
        objects.reserve(action->parameters.size());

        for (int i = 0; i < iterationSize; i++)
            objects.push_back((*iteration[i]));

        if (IsLegal(&action->preconditions, state, &objects))
            legalActions.push_back(PDDLActionInstance(action, objects));

    } while (Iterate(&iteration, &candidateObjects));
 
    return legalActions;
}

bool ActionGenerator::GetCandidateObjects(vector<unordered_set<unsigned int>> &candidateObjects, const PDDLAction *action, const PDDLState *state) const {
    const int parameterLength = action->parameters.size();
    for (int i = 0; i < parameterLength; i++) {
        std::unordered_set<unsigned int> tempCandididateObjects = GetCandidateObjects(&action->applicableUnaryLiterals.at(i), state);
        // if some parameter doesn't have any candidate object, the action is not possible
        if (tempCandididateObjects.size() == 0)
            return false;
        candidateObjects.push_back(tempCandididateObjects);
    }
    return true;
}

unordered_set<unsigned int> ActionGenerator::GetCandidateObjects(const unordered_set<const PDDLLiteral*> *literals, const PDDLState *state) const {
    if (literals->size() == 0) {
        const int objectCount = problem->objects.size();
        unordered_set<unsigned int> candidateObjects;
        candidateObjects.reserve(objectCount);
        for (int i = 0; i < problem->objects.size(); i++)
            candidateObjects.emplace(i);
        return candidateObjects;
    } else {
        unordered_set<unsigned int> candidateObjects;

        for (auto iter = literals->begin(); iter != literals->end(); iter++)
            if ((*iter)->value == true) {
                candidateObjects = state->unaryFacts.at((*iter)->predicateIndex);
                break;
            }
        RemoveIllegal(candidateObjects, literals, state);

        return candidateObjects;
    }
}

void ActionGenerator::RemoveIllegal(std::unordered_set<unsigned int> &set, const std::unordered_set<const PDDLLiteral*> *literals, const PDDLState *state) {
    for (auto literal = literals->begin(); literal != literals->end(); literal++)
        RemoveIllegal(set, (*literal), state);
}

void ActionGenerator::RemoveIllegal(std::unordered_set<unsigned int> &set, const PDDLLiteral *literal, const PDDLState *state) {
    // Find intersection of candidateobjects and the new literal
    const std::unordered_set<unsigned int> *newObjectRef = &(state->unaryFacts.at(literal->predicateIndex));
    // Returns true, i.e. object should be deleted, depending on the literal state
    const auto NewObjectNegContains = [&](auto const& x) { return newObjectRef->contains(x) != literal->value; };
    // Remove those which are(n't) contained in both depending on literal value
    std::erase_if(set, NewObjectNegContains);
}

bool ActionGenerator::IsLegal(const vector<PDDLLiteral> *literals, const PDDLState *state, vector<unsigned int> *objects) {
    const int literalsLength = literals->size();
    for (int i = 0; i < literalsLength; i++) {
        const PDDLLiteral *literal = &(literals->at(i));
        if (literal->args.size() == 1)
            continue;
        if (!IsLegal(literal, state, objects))
            return false;
    }
    return true;
}

bool ActionGenerator::IsLegal(const PDDLLiteral *literal, const PDDLState *state, std::vector<unsigned int> *objects) {
    if (literal->predicateIndex == 0) {
        if ((objects->at(0) == objects->at(1)) != literal->value)
            return false;
        else
            return true;
    } else {
        if (state->ContainsFact(literal->predicateIndex, objects) != literal->value)
            return false;
        else
            return true;
    }
}

bool ActionGenerator::Iterate(vector<unordered_set<unsigned int>::iterator> *iteration, vector<unordered_set<unsigned int>> *candidateObjects) {
    int incrementIndex = -1;
    for (int i = 0; i < iteration->size(); i++) {
        auto next = std::next((*iteration)[i], 1);
        if (next != (*candidateObjects)[i].end()) {
            (*iteration)[i]++;
            incrementIndex = i;
            break;
        }
    }
    for (int i = 0; i < incrementIndex; i++)
        (*iteration)[i] = (*candidateObjects)[i].begin();
    return (incrementIndex != -1);
}
