#ifndef SameOutputReformulator_HH
#define SameOutputReformulator_HH

#include "BaseReformulator.hh"
#include "../Config/Config.hh"
#include "../Helpers/ConsoleHelper.hh"

class SameOutputReformulator : public BaseReformulator {
public:
	SameOutputReformulator(Config *config) : BaseReformulator(config) {

	}
	PDDLInstance ReformulatePDDL(PDDLInstance* instance) override;
	SASPlan RebuildSASPlan(SASPlan* reformulatedSAS) override;
};

#endif