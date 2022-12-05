#include <catch2/catch_test_macros.hpp>

#include "../../src/Learner/Learner.hh"
#include "../../src/PlanGenerator/PlanGenerator.hh"

const std::string TAG = "Learner ";

TEST_CASE(TAG + "Domain = gripper"){
    Config config;
    PlanGenerator gen;
    Learner learner;

	std::filesystem::path fileName = std::filesystem::path("baseSettings.ini");
    std::string domainPath = "gripper";
	config.ParseConfigFile(fileName); 
    
    std::vector<std::pair<SASPlan, PDDLInstance>> plans = gen.GenerateSASPlans(config, domainPath);
    
    learner.IteratePlans(plans);
    REQUIRE(1==0);
}