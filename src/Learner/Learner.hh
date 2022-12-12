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

typedef std::vector<PDDLAction> MacroT;
typedef std::vector<MacroT> MacroList;

class Learner {
private:
    std::map<std::string, int> os;
    std::map<std::string, int> goalViolations;
    std::map<std::string, int> initViolations;
    std::vector<std::string> ops;
    std::vector<std::pair<int, std::vector<std::string>>> predIntersect(PDDLAction iAct, SASAction iSASAct, PDDLAction jAct, SASAction jSASAct);
    bool checkPredicates(PDDLInstance &pddl, MacroT acts, SASAction sAct, int flag);
    MacroList descendActions(PDDLInstance &pddl, std::vector<std::pair<PDDLAction, int>> entanglements, std::vector<SASPlan> plans);
    MacroList GetCandidates(PDDLDomain &domain, MacroT acts, std::vector<SASPlan> plans);
    MacroList FilterCandidates(MacroList candidates);
    MacroT RepetitiveFilter(MacroT candidate);
    MacroT lookupRanges(int start, int end, MacroT candidate);
    bool checkDependent(PDDLDomain &domain, SASPlan &plan, int j, MacroT mac);
public:
    enum EntangType {Init, Goal};

    // todo: put in settings
    double flawRatio = .5;
    double macroFlawRatio = .95;

    //MacroList IteratePlans(std::vector<std::pair<SASPlan, PDDLInstance*>> plans);
    MacroList IteratePlans(PlanGenerator gen);
    void AnalyzePlan(PDDLInstance &pddl, SASPlan plan);
};

#endif