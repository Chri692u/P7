#include "PDDLDomain.hh"

using namespace std;

vector<PDDLArg> PDDLDomain::GetArguments(const StringList* params, const TypeDict* types) {
    vector<PDDLArg> args;
    unordered_map<string, string> tempTypeDict;
    // Get types
    if (types != nullptr) {
        for (auto const& [x, y] : *types) {
            tempTypeDict.emplace(x, y);
        }
    }

    for (int i = 0; i < params->size(); i++) {
        auto p = (*params)[i];
        if (tempTypeDict.find((*params)[i]) == tempTypeDict.end())
            args.push_back(PDDLArg((*params)[i], nullptr));
        else
            args.push_back(PDDLArg((*params)[i], typeDict[tempTypeDict[(*params)[i]]]));
    }
    return args;
}

void PDDLDomain::AddTypes(const TypeDict* types) {
    if (types != nullptr) {
        for (auto const& [x, y] : *types) {
            // Check if type already exists
            if (typeDict.find(y) == typeDict.end())
                typeDict.emplace(y, new PDDLType(y));
        }
    }
}

vector<PDDLLiteral> PDDLDomain::GetLogicalExpressions(const vector<pair<Predicate*, bool>*>* logExp) {
    vector<PDDLLiteral> predicates;
    for (auto const& exp : *logExp) {
        vector<PDDLArg> args = GetArguments(exp->first->_args, exp->first->_types);
        predicates.push_back(PDDLLiteral(PDDLPredicate(exp->first->_name, args), exp->second));
    }
    return predicates;
}