#include "SameOutputReformulator.hh"

using namespace std;

PDDLInstance SameOutputReformulator::ReformulatePDDL(PDDLInstance* instance) {
	ConsoleHelper::PrintWarning("Note, this reformulator is only for testing! Simply gives the same result back.", 1);

	PDDLInstance newInstance(instance->domain, instance->problem);

	return newInstance;
}

SASPlan SameOutputReformulator::RebuildSASPlan(SASPlan* reformulatedSAS) {
	SASPlan newPlan(reformulatedSAS->actions, reformulatedSAS->cost);
	return newPlan;
}