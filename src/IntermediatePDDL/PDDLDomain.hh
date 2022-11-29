#ifndef PDDL_DOMAIN_HH
#define PDDL_DOMAIN_HH

#include <vector>
#include <string>
#include <unordered_map>
#include <map>

#include "PDDLPredicate.hh"
#include "PDDLAction.hh"
#include "../PDDLParser/domain.hh"

struct PDDLDomain {
    const std::string name;
    const std::vector<std::string> requirements;
    const std::vector<PDDLPredicate> predicates;
    // Goes from predicate name to index in "predicates"
    // e.g. "ROOM" => 0, "IsBall" => 1,...
    const std::unordered_map<std::string, unsigned int> predicateMap;
    const std::vector<PDDLAction> actions;
    // Set of predicates which are in no effects
    const std::unordered_set<unsigned int> staticPredicates;
    PDDLAction getAction(std::string name) {
        for (auto act : actions) {
            if (act.name == name) {
                return act;
            }
        }
        return PDDLAction(name);
    }
    PDDLDomain() : name("Not Set") {};
    PDDLDomain(std::vector<PDDLAction> actions) : name("Only actions"), actions(actions) {};
    PDDLDomain(std::string name, std::vector<std::string> requirements, std::vector<PDDLPredicate> predicates, 
    std::unordered_map<std::string, unsigned int> predicateMap, std::vector<PDDLAction> actions) :
    name(name), requirements(requirements), predicates(predicates), 
    predicateMap(predicateMap), actions(actions), staticPredicates(GetStaticPredicates()) {}; 

private:
    std::unordered_set<unsigned int> GetStaticPredicates() {
        std::unordered_set<unsigned int> candidateIndexes; candidateIndexes.reserve(predicates.size());
        for (int i = 1; i < predicates.size(); i++)
            candidateIndexes.emplace(i);
        for (auto iter = actions.begin(); iter != actions.end(); iter++) {
            for (auto litIter = (*iter).effects.begin(); litIter != (*iter).effects.end(); litIter++) {
                if (candidateIndexes.contains((*litIter).predicateIndex))
                    candidateIndexes.erase((*litIter).predicateIndex);
            }
        }
        return candidateIndexes;
    }
};

#endif
