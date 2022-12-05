#ifndef PLANGENERATOR_HH
#define PlANGENERATOR_HH

#include "../Config/config.hh"
#include "../DownwardRunner/DownwardRunner.hh"
#include "../SASParser/SASParser.hh"
#include "../PDDLParser/pddldriver.hh"
#include "../IntermediatePDDL/PDDLConverter.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class PlanGenerator {
public:
   std::vector<std::pair<SASPlan, PDDLInstance>> GenerateSASPlans(Config config, std::string domainFolder);
};

#endif