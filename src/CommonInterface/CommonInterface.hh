#ifndef CommonInterface_HH
#define CommonInterface_HH

#include <string>

#include "../RunReport/RunReport.hh"
#include "../PathCheckers/PathChecker.hh"
#include "../Reformulators/BaseReformulator.hh"
#include "../Reformulators/SameOutputReformulator.hh"
#include "../Reformulators/WalkerReformulator.hh"
#include "../PDDLParser/pddldriver.hh"
#include "../PDDLCodeGenerator/PDDLCodeGenerator.hh"
#include "../SASCodeGenerator/SASCodeGenerator.hh"
#include "../SASParser/SASParser.hh"
#include "../Config/Config.hh"
#include "../DownwardRunner/DownwardRunner.hh"
#include "../PlanValidators/PlanValidator.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../IntermediatePDDL/PDDLConverter.hh"
#include "../Helpers/ConsoleHelper.hh"

class CommonInterface {
public:
	enum RunResult { None, RanWithoutErrors, ErrorsEncountered };
	CommonInterface(Config config, std::string tempDomainName = "tempDomain.pddl", std::string tempProblemName = "tempProblem.pddl", std::string fastDownwardSASName = "sas_plan", std::string outputSASName = "real_sas_plan") :
	config(config), TempDomainName(tempDomainName), TempProblemName(tempProblemName), FastDownwardSASName(fastDownwardSASName), OutputSASName(outputSASName){};

	enum RunResult Run(RunReport* report);

private:
	Config config;
	std::string TempDomainName;
	std::string TempProblemName;
	std::string FastDownwardSASName;
	std::string OutputSASName;
	
};

#endif
