#ifndef PDDL_STATE_HH
#define PDDL_STATE_HH

#include <vector>
#include <unordered_map>

#include "PDDLPredicate.hh"
#include "PDDLLiteral.hh"
#include "PDDLAction.hh"

// This is a seperate class for future proofing
class PDDLState {
public:
    // Refers to the given problems objects
    std::vector<std::string> *objects;
    std::vector<PDDLPredicate> state;

    bool IsUnaryLiteralTrue(PDDLAction *action, PDDLLiteral literal, std::string object);
    bool IsMultiLiteralTrue(PDDLAction *action, PDDLLiteral literal, std::vector<std::string> objects);
    // Changes the state to be in accordance to the literal
    // Returns true if it inserts a new state
    bool Update(PDDLAction *action, PDDLLiteral literal, std::vector<std::string> objects);
private:
    int HasPredicate(PDDLAction *action, PDDLPredicate predicate, std::string object);
    int HasPredicate(PDDLAction *action, PDDLPredicate predicate, std::vector<std::string> objects);
    bool AreEqual(std::string arg1, std::string arg2);
};

#endif
