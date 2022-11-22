#ifndef PLANGENERATOR_HH
#define PlANGENERATOR_HH

#include "../Config/config.hh"
#include "../SASParser/SASParser.hh"

class PlanGenerator {
public:
    std::vector<SASPlan> GenerateSASPlans(Config config, std::string path);
};

#endif