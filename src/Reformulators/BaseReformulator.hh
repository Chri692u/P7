#ifndef BaseReformulator_HH
#define BaseReformulator_HH

#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../SASParser/SASParser.hh"
#include "../Config/Config.hh"

class BaseReformulator {
public:
	BaseReformulator(Config* config) : Configs(config) {

	}

	virtual PDDLInstance ReformulatePDDL(PDDLInstance* instance) = 0;
	virtual SASPlan RebuildSASPlan(SASPlan* reformulatedSAS) = 0;
protected:
	Config* Configs;
};

#endif