#include "RandomWalkerReformulator.hh"

using namespace std;

PDDLInstance RandomWalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {
	RandomHeuristic<PDDLActionInstance> *heu = new RandomHeuristic<PDDLActionInstance>(PDDLContext(instance->domain, instance->problem));
	BaseWidthFunction *widthFunc;
	if (Configs->ReformulatorTime.Content == -1)
		widthFunc = new ConstantWidthFunction(100);
	else
		widthFunc = new TimeWidthFunction(Configs->ReformulatorTime.Content);
	auto depthFunction = new ConstantDepthFunction(100, *instance);
	std::vector<Path> paths;
	unsigned int totalActionCount = 0;
	unsigned int totalIterations = 0;
	auto startTime = chrono::steady_clock::now();
	for (int i = 0; i < widthFunc->GetWidth(); i++) {
		Walker walker = Walker(instance,
			ActionGenerator(instance->domain, instance->problem),
			heu,
			depthFunction);
		paths.push_back(walker.Walk());

		// Debug info
		if (Configs->DebugMode.Content) {
			totalActionCount += walker.totalActions;
			totalIterations++;
		}
	}
	auto endTime = chrono::steady_clock::now();

	// Print debug info
	if (Configs->DebugMode.Content) {
		auto ellapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
		ConsoleHelper::PrintDebugInfo("[Walker] Total walk time:         " + to_string(ellapsed) + "ms", 1);
		double iterationsPrSecond = (totalIterations * 1000) / ellapsed;
		ConsoleHelper::PrintDebugInfo("[Walker] Total walker iterations: " + to_string(totalIterations) + " [" + to_string(iterationsPrSecond) + "/s]", 1);
		double actionsPrSecond = (totalActionCount * 1000) / ellapsed;
		ConsoleHelper::PrintDebugInfo("[Walker] Total actions Generated: " + to_string(totalActionCount) + " [" + to_string(actionsPrSecond) + "/s]", 1);
	}

	// Do Something and transform the input PDDL into a new PDDL format
	PDDLInstance newInstance(instance->domain, instance->problem);

	free(heu); free(widthFunc); free(depthFunction);

	return *instance;
}

SASPlan RandomWalkerReformulator::RebuildSASPlan(SASPlan* reformulatedSAS) {
	// Do Something and give a "corrected" SAS plan back
	SASPlan newPlan(reformulatedSAS->actions, reformulatedSAS->cost);
	return newPlan;
} 