#ifndef LEARNER_HH
#define LEARNER_HH


#include "../SASParser/SASParser.hh"
#include "../IntermediatePDDL/PDDLAction.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class Learner {
private:
    std::map<std::string, int> os;
    std::map<std::string, int> goalViolations;
    std::map<std::string, int> initViolations;
    std::vector<std::string> ops;
    bool checkPredicates(PDDLProblem prob, std::vector<PDDLAction> acts, SASAction sAct, int flag);
    std::vector<std::vector<PDDLAction>> descendActions(PDDLInstance pddl, std::vector<std::pair<PDDLAction, int>> entanglements, std::vector<SASPlan> plans);
    std::vector<std::vector<PDDLAction>> GetCandidates(PDDLInstance pddl, std::vector<PDDLAction> acts, std::vector<SASPlan> plans);
public:
    enum EntangType {Init, Goal};

    double flawRatio = 0.1;
    double macroFlawRatio = 0.3;

    std::vector<std::vector<PDDLAction>> IteratePlans(std::vector<SASPlan> plans, PDDLInstance pddl);
    void AnalyzePlan(PDDLInstance pddl, SASPlan plan);
};

#endif