#ifndef LEARNER_HH
#define LEARNER_HH


#include "../SASParser/SASParser.hh"
#include "../IntermediatePDDL/PDDLAction.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

typedef std::vector<PDDLAction> Macro;
typedef std::vector<Macro> MacroList;

class Learner {
private:
    std::map<std::string, int> os;
    std::map<std::string, int> goalViolations;
    std::map<std::string, int> initViolations;
    std::vector<std::string> ops;
    std::vector<std::pair<int, std::vector<std::string>>> predIntersect(PDDLInstance pddl, PDDLAction iAct, SASAction iSASAct, PDDLAction jAct, SASAction jSASAct);
    bool checkPredicates(PDDLProblem prob, Macro acts, SASAction sAct, int flag);
    std::vector<Macro> descendActions(PDDLInstance pddl, std::vector<std::pair<PDDLAction, int>> entanglements, std::vector<SASPlan> plans);
    std::vector<Macro> GetCandidates(PDDLInstance pddl, Macro acts, std::vector<SASPlan> plans);
    MacroList FilterCandidates(MacroList candidates);
    Macro RepetitiveFilter(Macro candidate);
    Macro lookupRanges(int start, int end, Macro candidate);
public:
    enum EntangType {Init, Goal};

    // todo: put in settings
    double flawRatio = 0.1;
    double macroFlawRatio = 0.3;

    std::vector<Macro> IteratePlans(std::vector<SASPlan> plans, PDDLInstance pddl);
    void AnalyzePlan(PDDLInstance pddl, SASPlan plan);
};

#endif