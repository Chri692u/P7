#include "PDDLAction.hh"

int PDDLAction::GetParamIndex(std::string paramName) {
    if (paramIndexMap.find(paramName) != paramIndexMap.end())
        return paramIndexMap[paramName];
    else
        throw std::invalid_argument("Received request for non existent parameter: " + paramName);
}