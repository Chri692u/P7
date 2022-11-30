#ifndef PLANGENERATOR_HH
#define PlANGENERATOR_HH

#include "../Config/config.hh"
#include "../SASParser/SASParser.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"

class PlanGenerator {
public:
   std::vector<std::pair<SASPlan, PDDLInstance>> GenerateSASPlans(Config config, std::string path);
};

#endif