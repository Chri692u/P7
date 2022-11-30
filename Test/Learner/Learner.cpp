#include <catch2/catch_test_macros.hpp>

#include "../../src/Learner/Learner.hh"
#include "../../src/PlanGenerator/PlanGenerator.hh"

const std::string TAG = "Learner ";

TEST_CASE(TAG + "Domain = gripper") {
    Config config;

	std::filesystem::path fileName = std::filesystem::path("settings.ini");
	if (argc > 1)
		fileName = std::filesystem::path(argv[1]);
        
	config.ParseConfigFile(fileName); 
    PlanGenerator gen;
    Learner learner;

    std::vector<SASPlan> plans = gen.GenerateSASPlans(config, "/gripper/");
    //get pddl domain + problem
    learner.IteratePlans(plans, ); //learner skal tage det nye par ind, så det skal fixes før det her kan lade sig gøre
    REQUIRE();
}