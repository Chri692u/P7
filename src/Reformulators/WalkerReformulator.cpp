#include "WalkerReformulator.hh"

using namespace std;

PDDLInstance WalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {
	// Walk the PDDL
	auto paths = PerformWalk(instance);

	// Find Entangelements
	auto candidates = FindEntanglements(&paths, instance);

	// Generate new Macros
	auto newInstance = GenerateMacros(candidates, instance);

	return *instance;
}

vector<Path> WalkerReformulator::PerformWalk(PDDLInstance* instance) {
	Walker walker = Walker(instance, ActionGenerator(instance->domain, instance->problem), Configs);
	BaseHeuristic *heuristic;
	if (Configs->GetString("heuristic") == "random")
		heuristic = new RandomHeuristic();
	else if (Configs->GetString("heuristic") == "goalCount")
		heuristic = new GoalCountHeuristic(instance->domain, instance->problem);
	else
		throw std::invalid_argument("Invalid heuristic specified in config");
		
		
	BaseDepthFunction *depthFunc = new ConstantDepthFunction(1000, *instance, 1);
	BaseWidthFunction *widthFunc;
	if (Configs->GetInteger("timelimit") != -1)
		widthFunc = new TimeWidthFunction(Configs->GetInteger("timelimit"));
	else
		widthFunc = new ConstantWidthFunction(100000);

	auto startTime = chrono::steady_clock::now();
	std::vector<Path> paths = walker.Walk(heuristic, depthFunc, widthFunc);
	free(heuristic); free(widthFunc); free(depthFunc);
	auto endTime = chrono::steady_clock::now();

	// Print debug info
	if (Configs->GetBool("debugmode")) {
		unsigned int totalIterations = paths.size();
		unsigned int totalActionCount = walker.GetTotalActionsGenerated();
		auto ellapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
		ConsoleHelper::PrintDebugInfo("[Walker] Total walk time:         " + to_string(ellapsed) + "ms", 1);
		double iterationsPrSecond = (totalIterations * 1000) / ellapsed;
		ConsoleHelper::PrintDebugInfo("[Walker] Total walker iterations: " + to_string(totalIterations) + " [" + to_string(iterationsPrSecond) + "/s]", 1);
		double actionsPrSecond = (totalActionCount * 1000) / ellapsed;
		ConsoleHelper::PrintDebugInfo("[Walker] Total actions Generated: " + to_string(totalActionCount) + " [" + to_string(actionsPrSecond) + "/s]", 1);
	}

	return paths;
}

unordered_map<size_t, EntanglementOccurance> WalkerReformulator::FindEntanglements(vector<Path>* paths, PDDLInstance* instance) {
	EntanglementFinder entFinder;

	if (Configs->GetBool("debugmode")) {
		ProgressBarHelper* bar;
		entFinder.OnNewLevel = [&](int level, int outOf) {
			bar = new ProgressBarHelper(outOf, "Finding Entanglements (level " + to_string(level) + ")", 1);
		};
		entFinder.OnLevelIteration = [&](int current, int outOf) {
			bar->Update();
		};
		entFinder.OnLevelEnd = [&]() {
			bar->End();
		};
	}

	auto startTime = chrono::steady_clock::now();
	auto candidates = entFinder.FindEntangledCandidates(paths);
	auto endTime = chrono::steady_clock::now();

	if (Configs->GetBool("printentanglersteps")) {
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Entanglements:", 1);
		for (auto i = candidates.begin(); i != candidates.end(); i++) {
			string actionStr = "";
			for (int j = 0; j < (*i).second.Chain.size(); j++) {
				auto item = (*i).second.Chain.at(j);
				string paramStr = "";
				for (int l = 0; l < item->objects.size(); l++) {
					paramStr += instance->problem->objects[item->objects[l]];
					if (l != item->objects.size() - 1)
						paramStr += ", ";
				}
				actionStr += item->action->name + "(" + paramStr + ")";
				if (j != (*i).second.Chain.size() - 1)
					actionStr += " -> ";
			}
			ConsoleHelper::PrintDebugInfo("[Entanglement Finder] " + to_string((*i).second.Occurance) + " : " + to_string((*i).second.BetweenDifferentPaths) + " : " + actionStr, 2);
		}
	}
	if (Configs->GetBool("debugmode")) {
		unsigned int totalActions = 0;
		for (int i = 0; i < paths->size(); i++)
			totalActions += paths->at(i).steps.size();

		auto ellapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total search time:         " + to_string(ellapsed) + "ms", 1);
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Levels:              " + to_string(entFinder.TotalLevels()), 1);
		double comparisonsPrSecond = (entFinder.TotalComparisons()) / ellapsed;
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Comparisons:         " + to_string(entFinder.TotalComparisons()) + " [" + to_string(comparisonsPrSecond) + "k/s]", 1);
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Total Candidates:          " + to_string(candidates.size()) + " (" + to_string(entFinder.RemovedCandidates()) + " removed)", 1);
		ConsoleHelper::PrintDebugInfo("[Entanglement Finder] Path Data:                 " + to_string(paths->size()) + " paths with " + to_string(totalActions) + " steps in total", 1);
	}

	return candidates;
}

PDDLInstance WalkerReformulator::GenerateMacros(unordered_map<size_t, EntanglementOccurance> candidates, PDDLInstance* instance) {
	PDDLInstance newInstance(instance->domain, instance->problem);
	return newInstance;
}

SASPlan WalkerReformulator::RebuildSASPlan(SASPlan* reformulatedSAS) {
	// Do Something and give a "corrected" SAS plan back
	SASPlan newPlan(reformulatedSAS->actions, reformulatedSAS->cost);
	return newPlan;
} 
