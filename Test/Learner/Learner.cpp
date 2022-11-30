#include <catch2/catch_test_macros.hpp>

#include "../../src/Learner/Learner.hh"
#include "../../src/PlanGenerator/PlanGenerator.hh"

const std::string TAG = "Learner ";

TEST_CASE(TAG + "Domain = gripper") {
    Config config = Config();
    PlanGenerator gen = PlanGenerator();
    REQUIRE();
}