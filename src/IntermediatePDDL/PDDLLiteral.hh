#ifndef PDDL_LITERAL_HH
#define PDDL_LITERAL_HH

#include <string>

#include "PDDLPredicate.hh"

struct PDDLLiteral {
    PDDLPredicate predicate;
    bool state;
    PDDLLiteral(PDDLPredicate predicate, bool state) : predicate(predicate), state(state) {};
};

#endif
