#ifndef LEARNER_HH
#define LEARNER_HH


#include "../SASParser/SASParser.hh"
#include "../IntermediatePDDL/PDDLAction.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class Learner {
public:
    double flawRatio = 0.1;
    std::vector<std::vector<PDDLAction>> IteratePlans(std::vector<SASPlan> plans, PDDLInstance pddl);
    std::vector<std::pair<SASAction, int>> AnalyzePlan(PDDLInstance pddl, SASPlan plan);
    bool checkPredicates(PDDLProblem prob, std::vector<PDDLAction> acts, SASAction sAct, int flag);
};

#endif