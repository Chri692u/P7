#ifndef WALKER
#define WALKER

#include <vector>

#include "../IntermediatePDDL/PDDLActionInstance.hh"
#include "Heuristics/BaseHeuristics.hh"
#include "Heuristics/Contexts/PDDLContext.hh"
#include "DepthFunctions/BaseDepthFunction.hh"
#include "DepthFunctions/ObjectActionDepthFunction.hh"
#include "ActionGenerator.hpp"

class Path {
public:
    Path() {};
    Path(std::vector<PDDLActionInstance> steps) : steps(steps) {};
    void AddStep(PDDLActionInstance step) {
        steps.push_back(step);
    }
    std::vector<PDDLActionInstance> GetSteps() {
        return steps;
    }

private:
    std::vector<PDDLActionInstance> steps;
};

class Walker {
public:
    Walker(PDDLInstance* instance, ActionGenerator actionGenerator, BaseHeuristics<PDDLActionInstance, PDDLContext>* heuristic, BaseDepthFunction* depthFunc) : instance(instance), actionGenerator(actionGenerator), heuristic(heuristic), depthFunc(depthFunc) {}
    Path Walk();
    Path Walk(PDDLState state);
private:
    PDDLInstance* instance;
    ActionGenerator actionGenerator;
    BaseHeuristics<PDDLActionInstance, PDDLContext>* heuristic;
    BaseDepthFunction* depthFunc;

    PDDLState DoAction(PDDLState state, PDDLActionInstance action);
};

#endif
