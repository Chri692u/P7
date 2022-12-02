#include <catch2/catch_test_macros.hpp>

#include "../../src/Learner/Learner.hh"
#include "../../src/PlanGenerator/PlanGenerator.hh"

const std::string TAG = "Learner ";

TEST_CASE(TAG + "Domain = gripper") {
    Config config;
    PlanGenerator gen;
    Learner learner;

	std::filesystem::path fileName = std::filesystem::path("./settings.ini");
    std::string domainPath = "./gripper/domain.pddl";
	config.ParseConfigFile(fileName); 
    
    /*
    due to unexpected exception with message:
    filesystem error: directory iterator cannot open directory: Not a directory
    [./gripper/domain.pddl]
    */
    std::vector<std::pair<SASPlan, PDDLInstance>> plans = gen.GenerateSASPlans(config, domainPath);

    learner.IteratePlans(plans);
    REQUIRE(1==0);
}