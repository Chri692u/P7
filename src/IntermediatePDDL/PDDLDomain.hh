#ifndef PDDL_DOMAIN_HH
#define PDDL_DOMAIN_HH

#include <vector>
#include <string>
#include <unordered_map>
#include <map>

#include "PDDLType.hh"
#include "PDDLArg.hh"
#include "PDDLPredicate.hh"
#include "PDDLLiteral.hh"
#include "PDDLAction.hh"

#include "../PDDLParser/domain.hh"

class PDDLDomain {
public:
    std::string name;
    std::unordered_map<std::string, PDDLType*> typeDict;
    std::vector<std::string> requirements;
    std::vector<PDDLPredicate> predicates;
    std::vector<PDDLAction> actions;

    PDDLDomain() {
        name = "Not Set";
    }

    PDDLDomain(PDDLDomain* domain) {
    }

    PDDLDomain(Domain* domain) {
        name = domain->_name.c_str();
        // Get Requirements
        for (int i = 0; i < domain->_requirements->size(); i++)
            requirements.push_back((*domain->_requirements)[i]);

        // Get Predicates
        for (auto const& predicate : *domain->_predicates) {
            AddTypes(predicate->_types);
            predicates.push_back(PDDLPredicate(predicate->_name,  GetArguments(predicate->_args, predicate->_types)));
        }  

        // Get Actions
        for (auto const& action : *domain->_actions) {
            PDDLAction newAction = PDDLAction(action->_name, GetArguments(action->_params, action->_types),
            GetLogicalExpressions(action->_precond), GetLogicalExpressions(action->_effects));
            actions.push_back(newAction);
        }
    };

    std::vector<PDDLArg> GetArguments(const StringList* params, const TypeDict* types);

private:
    void AddTypes(const TypeDict* types);
    std::vector<PDDLLiteral> GetLogicalExpressions(const std::vector<std::pair<Predicate*, bool>*>* logExp);
};

#endif
