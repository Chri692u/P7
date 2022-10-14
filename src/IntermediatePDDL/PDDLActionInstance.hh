#ifndef PDDL_ACTION_INSTANCE_HH
#define PDDL_ACTION_INSTANCE_HH

#include <vector>
#include <string>

#include "PDDLAction.hh"

class PDDLActionInstance {
public:
    PDDLAction action;
    std::vector<std::string> arguments;
    PDDLActionInstance(PDDLAction action, std::vector<std::string> arguments) : action(action), arguments(arguments) {};
private:
};

#endif
