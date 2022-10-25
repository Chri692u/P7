#ifndef PDDL_LITERAL_HH
#define PDDL_LITERAL_HH

#include <vector>

struct PDDLLiteral {
    // Index of domain predicate list
    const unsigned int predicateIndex;
    // What parameter index of action the given argument position refers to
    const std::vector<unsigned int> args;
    // What value the predicate should be with the given arguments
    const bool value;
    PDDLLiteral(const unsigned int predicateIndex, const std::vector<unsigned int> args, const bool value) :
        predicateIndex(predicateIndex), args(args), value(value) {};
    friend bool operator==(const PDDLLiteral &lhs, const PDDLLiteral &rhs) {
        if (lhs.predicateIndex != rhs.predicateIndex)
            return false;
        if (lhs.args != rhs.args)
            return false;
        if (lhs.value != rhs.value)
            return false;
        return true;
    }
};

#endif
