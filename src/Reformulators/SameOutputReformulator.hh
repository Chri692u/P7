#ifndef SameOutputReformulator_HH
#define SameOutputReformulator_HH

#include "BaseReformulator.hh"
#include "../Config/Config.hh"
#include "../Helpers/ConsoleHelper.hh"

class SameOutputReformulator : public BaseReformulator {
public:
	SameOutputReformulator(Config *config, RunReport* report) : BaseReformulator(config, report) {

	}
	PDDLInstance ReformulatePDDL(PDDLInstance* instance, std::vector<std::vector<PDDLAction>> &macs) override;
	SASPlan RebuildSASPlan(PDDLInstance *instance, SASPlan* reformulatedSAS) override;
};

#endif