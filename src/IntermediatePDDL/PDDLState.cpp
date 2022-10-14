#include "PDDLState.hh"

using namespace std;

bool PDDLState::IsUnaryLiteralTrue(PDDLAction *action, PDDLLiteral literal, string object) {
    if (this->HasPredicate(action, literal.predicate, object) != -1)
        return literal.state;
    else
        return !literal.state;
}

bool PDDLState::IsMultiLiteralTrue(PDDLAction *action, PDDLLiteral literal, vector<string> objects) {
    if (literal.predicate.name == "=")
        return AreEqual(objects[action->GetParamIndex(literal.predicate.args[0].name)], objects[action->GetParamIndex(literal.predicate.args[1].name)]) == literal.state;
    if (HasPredicate(action, literal.predicate, objects) != -1)
        return literal.state;
    else
        return !literal.state;
}

bool PDDLState::Update(PDDLAction *action, PDDLLiteral literal, std::vector<std::string> objects) {
    int predicateIndex = HasPredicate(action, literal.predicate, objects);
    if (predicateIndex == -1) {
        for (int i = 0; i < literal.predicate.args.size(); i++)
            literal.predicate.args[i].name = objects[action->GetParamIndex(literal.predicate.args[i].name)];
        state.push_back(literal.predicate);
        return true;
    } else {
        state.erase(state.begin() + predicateIndex);
        return false;
    }
}

int PDDLState::HasPredicate(PDDLAction *action, PDDLPredicate predicate, std::string object) {
    for (int i = 0; i < state.size(); i++)
        if (predicate.name == state[i].name && object == state[i].args[0].name)
            return i;
    return -1;
}

int PDDLState::HasPredicate(PDDLAction *action, PDDLPredicate predicate, std::vector<std::string> objects) {
    for (int i = 0; i < state.size(); i++) {
        if (state[i].name == predicate.name && state[i].args.size() == predicate.args.size()) {
            bool found = true;
            for (int o = 0; o < predicate.args.size(); o++) {
                int index = action->GetParamIndex(predicate.args[o].name);
                if (objects[index] != state[i].args[o].name) {
                    found = false;
                    break;
                }
            }
            if (found)
                return i;
        }
    }
    return -1;
}

bool PDDLState::AreEqual(std::string arg1, std::string arg2) {
    return arg1 == arg2;
}
