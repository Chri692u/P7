#ifndef PDDL_ACTION_HH
#define PDDL_ACTION_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include "PDDLArg.hh"
#include "PDDLLiteral.hh"

class PDDLAction {
public:
    std::string name;
    std::vector<PDDLArg> parameters;
    
    std::vector<PDDLLiteral> preconditions;
    std::vector<PDDLLiteral> effects;
    PDDLAction() {};
    PDDLAction(std::string name, std::vector<PDDLArg> parameters, std::vector<PDDLLiteral> preconditions, std::vector<PDDLLiteral> effects) :
        name(name), parameters(parameters), preconditions(preconditions), effects(effects) {
            for (int i = 0; i < this->parameters.size(); i++)
                paramIndexMap.emplace(this->parameters[i].name, i);
    };

    int GetParamIndex(std::string paramName);

private:
    std::unordered_map<std::string, int> paramIndexMap;
};

#endif
