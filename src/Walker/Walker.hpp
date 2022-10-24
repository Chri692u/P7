#ifndef WALKER
#define WALKER

#include <vector>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "Heuristics/BaseHeuristics.hh"
#include "Heuristics/Contexts/PDDLContext.hh"
#include "DepthFunctions/BaseDepthFunction.hh"
#include "DepthFunctions/ObjectActionDepthFunction.hh"
#include "ActionGenerator.hpp"
#include "../RunReport/RunReport.hh"

struct Path {
    const std::vector<PDDLActionInstance> steps;
    Path(std::vector<PDDLActionInstance> steps) : steps(steps) {};
};

class Walker {
public:
    unsigned int totalActions = 0;
    Walker(PDDLInstance* instance, ActionGenerator actionGenerator, BaseHeuristics<PDDLActionInstance, PDDLContext> *heuristic, BaseDepthFunction *depthFunc) : 
    instance(instance), actionGenerator(actionGenerator), heuristic(heuristic), depthFunc(depthFunc) {}
    Path Walk();
    Path Walk(PDDLState state);
    static void DoAction(PDDLState *state, const PDDLActionInstance *action);
private:
    PDDLInstance* instance;
    ActionGenerator actionGenerator;
    BaseHeuristics<PDDLActionInstance, PDDLContext> *heuristic;
    BaseDepthFunction *depthFunc;

    
};

#endif
