#ifndef WalkerReformulator_HH
#define WalkerReformulator_HH

#include <chrono>
#include <unordered_map>

#include "BaseReformulator.hh"
#include "../Walker/Walker.hpp"
#include "../Walker/Heuristics/RandomHeuristic.hh"
#include "../Walker/Heuristics/GoalCountHeuristic.hh"
#include "../Walker/DepthFunctions/ConstantDepthFunction.hh"
#include "../Walker/WidthFunctions/ConstantWidthFunction.hh"
#include "../Walker/WidthFunctions/TimeWidthFunction.hh"
#include "../Config/Config.hh"
#include "../Helpers/ConsoleHelper.hh"
#include "../EntanglementFinder/EntanglementFinder.hh"
#include "../EntanglementFinder/EntanglementOccurance.hh"
#include "../Helpers/ProgressBarHelper.hh"

class WalkerReformulator : public BaseReformulator {
public:
	WalkerReformulator(Config* config) : BaseReformulator(config) {

	}
	PDDLInstance ReformulatePDDL(PDDLInstance* instance) override;
	SASPlan RebuildSASPlan(SASPlan* reformulatedSAS) override;
private:
	std::vector<Path> PerformWalk(PDDLInstance* instance);
	std::unordered_map<size_t, EntanglementOccurance> FindEntanglements(std::vector<Path>* paths, PDDLInstance* instance);
	PDDLInstance GenerateMacros(std::unordered_map<size_t, EntanglementOccurance> candidates, PDDLInstance* instance);
};

#endif