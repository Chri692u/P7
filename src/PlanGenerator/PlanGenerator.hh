#ifndef PLANGENERATOR_HH
#define PlANGENERATOR_HH

#include "../Config/Config.hh"
#include "../DownwardRunner/DownwardRunner.hh"
#include "../SASParser/SASParser.hh"
#include "../PDDLParser/pddldriver.hh"
#include "../IntermediatePDDL/PDDLConverter.hh"
#include "../IntermediatePDDL/PDDLInstance.hh"
#include "../SASCodeGenerator/SASCodeGenerator.hh"

class PlanGenerator {
public:
   std::vector<PDDLDomain> domains;
   std::vector<PDDLProblem> problems;
   std::vector<SASPlan> sasplans;
   void GenerateSASPlans(Config config, std::string domainFolder);
};

#endif