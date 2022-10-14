#include "RandomWalkerReformulator.hh"

using namespace std;

// Move this...
#define WIDTH 10


PDDLInstance RandomWalkerReformulator::ReformulatePDDL(PDDLInstance* instance) {
	RandomHeuristic<PDDLActionInstance>* heu = new RandomHeuristic<PDDLActionInstance>(PDDLContext(instance->domain, instance->problem));
	ConstantWidthFunction widthFunc = ConstantWidthFunction(WIDTH, *instance);
	std::vector<Path> paths;
	for (int i = 0; i < widthFunc.GetWidth(); i++) {
		Walker walker = Walker(instance,
		ActionGenerator(instance->domain),
		heu,
		new ObjectActionDepthFunction(*instance));
		Path path = walker.Walk();
		paths.push_back(path);
	}
	

	// Do Something and transform the input PDDL into a new PDDL format
	PDDLInstance newInstance(instance->domain, instance->problem);

	return newInstance;
}

SASPlan RandomWalkerReformulator::RebuildSASPlan(SASPlan* reformulatedSAS) {
	// Do Something and give a "corrected" SAS plan back
	SASPlan newPlan(reformulatedSAS->actions, reformulatedSAS->cost);
	return newPlan;
}