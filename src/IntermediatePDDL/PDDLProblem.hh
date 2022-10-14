#ifndef PDDL_PROBLEM_HH
#define PDDL_PROBLEM_HH

#include <string>
#include <vector>

#include "../PDDLParser/problem.hh"
#include "PDDLArg.hh"
#include "PDDLLiteral.hh"
#include "PDDLPredicate.hh"
#include "PDDLDomain.hh"
#include "PDDLState.hh"

class PDDLProblem {
public:
    std::string name;
    PDDLDomain *domain;

    std::vector<std::string> objects;
    PDDLState initState;
    PDDLState goalState;

    PDDLProblem() {
        name = "Not Set";
    }

    PDDLProblem(Problem* problem, PDDLDomain *_domain) : name(problem->_name), domain(_domain) {
        for (auto const& object : *problem->_objects)
            objects.push_back(object);
        
        for (auto const& init : *problem->_init) {
            std::vector<PDDLArg> args = domain->GetArguments(init->first->_args, init->first->_types);
            initState.state.push_back(PDDLPredicate(init->first->_name, args));
        }
            
        for (auto const& goal : *problem->_goal) {
            std::vector<PDDLArg> args = domain->GetArguments(goal->first->_args, goal->first->_types);
            goalState.state.push_back(PDDLPredicate(goal->first->_name, args));
        }
        initState.objects = &objects;
        goalState.objects = &objects;
    }
private:
};

#endif
