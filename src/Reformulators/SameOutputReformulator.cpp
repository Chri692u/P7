#include "SameOutputReformulator.hh"

using namespace std;

PDDLInstance SameOutputReformulator::ReformulatePDDL(PDDLInstance* instance, vector<vector<PDDLAction>> &macs) {
	ConsoleHelper::PrintWarning("Note, this reformulator is only for testing! Simply gives the same result back.", 2);

	PDDLInstance newInstance(instance->domain, instance->problem);

	return newInstance;
}

SASPlan SameOutputReformulator::RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) {
	SASPlan newPlan(reformulatedSAS->actions, reformulatedSAS->cost);
	return newPlan;
}