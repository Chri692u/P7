#ifndef PDDL_ACTION_INSTANCE_HH
#define PDDL_ACTION_INSTANCE_HH

#include <vector>
#include <string>

#include "PDDLProblem.hh"
#include "PDDLDomain.hh"
#include "PDDLAction.hh"

struct PDDLProblem;

class PDDLActionInstance {
public:
    const PDDLAction *action;
    const std::vector<unsigned int> objects;
    PDDLActionInstance(const PDDLAction *action, const std::vector<unsigned int> objects) : action(action), objects(objects) {}; 
    std::string ToString(const PDDLProblem* problem, const PDDLDomain* domain);
    std::string LiteralsToString(std::vector<PDDLLiteral> literals, const PDDLDomain* domain, const PDDLProblem* problem);
    
    friend bool operator==(const PDDLActionInstance &lhs, const PDDLActionInstance &rhs) {
        if (lhs.action != rhs.action)
            return false;
        if (lhs.objects != rhs.objects)
            return false;
        return true;
    }
private:
};

#endif
