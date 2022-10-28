#ifndef PDDL_PREDICATE_HH
#define PDDL_PREDICATE_HH

#include <string>
#include <vector>

struct PDDLPredicate {
    const std::string name;
    // This is only used for later printing
    const std::vector<std::string> arguments;
    const int argumentCount;
    
    PDDLPredicate(int argumentCount) : argumentCount(argumentCount) {};
    PDDLPredicate(std::string name, int argumentCount) : name(name), argumentCount(argumentCount) {};
    PDDLPredicate(std::string name, std::vector<std::string> arguments, int argumentCount) : name(name), arguments(arguments), argumentCount(argumentCount) {};
};

#endif
