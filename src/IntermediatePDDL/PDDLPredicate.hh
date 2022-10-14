#ifndef PDDL_PREDICATE_HH
#define PDDL_PREDICATE_HH

#include <string>
#include <vector>

#include "PDDLArg.hh"

struct PDDLPredicate {
    std::string name;
    std::vector<PDDLArg> args;
    PDDLPredicate(std::string name, std::vector<PDDLArg> args) : name(name), args(args) {};
};

#endif
