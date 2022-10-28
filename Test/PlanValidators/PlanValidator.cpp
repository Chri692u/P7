#include <catch2/catch_test_macros.hpp>

#include "../../src/PlanValidators/PlanValidator.hh"
#include "../../src/Helpers/FileHelper.hh"

using namespace std;

const string TAG = "PlanValidator ";
const string domainFile = "./TestFiles/gripper.pddl";
const string problemFile = "./TestFiles/gripper-4.pddl";
const string goodPlan = "./TestFiles/good_plan";
const string badPlan = "./TestFiles/bad_plan";

TEST_CASE(TAG + "MissingVAL") {
    Config config;
    config.ParseConfigFile("PATH:validatorpath=notval");

    PlanValidator validator;
    PlanValidator::ValidatorResult res = validator.ValidatePlan(config, domainFile, problemFile, badPlan);
    REQUIRE(PlanValidator::ValidatorResult::MissingVAL == res);
}

TEST_CASE(TAG + "MissingDomainFile") {
    Config config;
    config.ParseConfigFile("PATH:validatorpath=notval");

    PlanValidator validator;
    PlanValidator::ValidatorResult res = validator.ValidatePlan(config, "Not a domain", problemFile, badPlan);
    REQUIRE(PlanValidator::ValidatorResult::MissingDomainFile == res);
}

TEST_CASE(TAG + "MissingProblemFile") {
    Config config;
    config.ParseConfigFile("PATH:validatorpath=notval");

    PlanValidator validator;
    PlanValidator::ValidatorResult res = validator.ValidatePlan(config, domainFile, "Not a problem", badPlan);
    REQUIRE(PlanValidator::ValidatorResult::MissingProblemFile == res);
}

TEST_CASE(TAG + "MissingPlanFile") {
    Config config;
    config.ParseConfigFile("PATH:validatorpath=notval");

    PlanValidator validator;
    PlanValidator::ValidatorResult res = validator.ValidatePlan(config, domainFile, problemFile, "Not a plan");
    REQUIRE(PlanValidator::ValidatorResult::MissingPlanFile == res);
}