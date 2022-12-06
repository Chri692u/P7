#ifndef LEARNER_HH
#define LEARNER_HH


#include "../SASParser/SASParser.hh"
#include "../IntermediatePDDL/PDDLAction.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../Config/Config.hh"
#include "../PlanGenerator/PlanGenerator.hh"
#include "unordered_set"
#include <map>
#include <ranges>

typedef std::vector<PDDLAction> Macro;
typedef std::vector<Macro> MacroList;

class Learner {
private:
    std::map<std::string, int> os;
    std::map<std::string, int> goalViolations;
    std::map<std::string, int> initViolations;
    std::vector<std::string> ops;
    std::vector<std::pair<int, std::vector<std::string>>> predIntersect(PDDLAction iAct, SASAction iSASAct, PDDLAction jAct, SASAction jSASAct);
    bool checkPredicates(PDDLInstance &pddl, Macro acts, SASAction sAct, int flag);
    std::vector<Macro> descendActions(PDDLInstance &pddl, std::vector<std::pair<PDDLAction, int>> entanglements, std::vector<SASPlan> plans);
    std::vector<Macro> GetCandidates(PDDLDomain &domain, Macro acts, std::vector<SASPlan> plans);
    MacroList FilterCandidates(MacroList candidates);
    Macro RepetitiveFilter(Macro candidate);
    Macro lookupRanges(int start, int end, Macro candidate);
public:
    enum EntangType {Init, Goal};

    // todo: put in settings
    double flawRatio = 0.1;
    double macroFlawRatio = 0.3;

    //MacroList IteratePlans(std::vector<std::pair<SASPlan, PDDLInstance*>> plans);
    MacroList IteratePlans(PlanGenerator gen);
    void AnalyzePlan(PDDLInstance &pddl, SASPlan plan);
};

#endif