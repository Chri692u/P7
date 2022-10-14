#include "SameOutputReformulator.hh"

using namespace std;

PDDLInstance SameOutputReformulator::ReformulatePDDL(PDDLInstance* instance) {
	cout << "Note, this reformulator is only for testing! Simply gives the same result back." << endl;
	// Do Something and transform the input PDDL into a new PDDL format
	PDDLInstance newInstance(instance->domain, instance->problem);

	return newInstance;
}

SASPlan SameOutputReformulator::RebuildSASPlan(SASPlan* reformulatedSAS) {
	// Do Something and give a "corrected" SAS plan back
	SASPlan newPlan(reformulatedSAS->actions, reformulatedSAS->cost);
	return newPlan;
}