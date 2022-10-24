#include "PDDLAction.hh"

std::vector<PDDLLiteral> PDDLAction::GetAdds() {
    std::vector<PDDLLiteral> return_vec;
    for (PDDLLiteral lit : (*this).effects) {
        if (lit.value) 
            return_vec.push_back(lit);
    }
    return return_vec;
}

std::vector<PDDLLiteral> PDDLAction::GetDeletes() {
    std::vector<PDDLLiteral> return_vec;
    for (PDDLLiteral lit : (*this).effects) {
        if (!lit.value) 
            return_vec.push_back(lit);
    }
    return return_vec;
}
std::unordered_map<unsigned int, const std::unordered_set<const PDDLLiteral*>> PDDLAction::GenerateApplicableLiterals(bool unary) {
    std::unordered_map<unsigned int, const std::unordered_set<const PDDLLiteral*>> set;
    if (parameters.size() == 0 || preconditions.size() == 0)
        return set;
    for (int i = 0; i < parameters.size(); i++) {
        std::unordered_set<const PDDLLiteral*> tempSet;
        for (int literalIndex = 0; literalIndex < preconditions.size(); literalIndex++) {
            const PDDLLiteral *literal = &preconditions.at(literalIndex);
            if (unary ? (literal->args.size() != 1) : (literal->args.size() == 1))
                continue;
            for (int argIndex = 0; argIndex < literal->args.size(); argIndex++)
                if (i == literal->args.at(argIndex))
                    tempSet.emplace(literal);
        }
        set.emplace(i, tempSet);
    }
    return set;
};
