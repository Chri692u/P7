#ifndef PDDL_LITERAL_HH
#define PDDL_LITERAL_HH

#include <vector>

struct PDDLLiteral {
    // Index of domain predicate list
    unsigned int predicateIndex;
    // What parameter index of action the given argument position refers to
    std::vector<unsigned int> args;
    // What value the predicate should be with the given arguments
    bool value;
    PDDLLiteral(const unsigned int predicateIndex, const std::vector<unsigned int> args, const bool value) :
        predicateIndex(predicateIndex), args(args), value(value) {};

    /// @return Returns true if the predicateIndex and arguments are the same, ignores value
    friend bool operator==(const PDDLLiteral& lhs, const PDDLLiteral& rhs) {
        if (lhs.predicateIndex != rhs.predicateIndex)
            return false;
        if (lhs.args != rhs.args)
            return false;
        // if (lhs.value != rhs.value)
        //     return false;
        return true;
    }
    /// @return Returns true if the predicateIndex and arguments are not the same
    friend bool operator!=(const PDDLLiteral& lhs, const PDDLLiteral& rhs) {
        return !(lhs == rhs);
    }
};

#endif
