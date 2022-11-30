#include <catch2/catch_test_macros.hpp>

#include "../../src/Learner/Learner.hh"
#include "../../src/PlanGenerator/PlanGenerator.hh"

const std::string TAG = "Learner ";

TEST_CASE(TAG + "Domain = gripper") {
    std::vector<PDDLActionInstance*> actions;
    // set up simple action with 1 precondition and 1 effect
    PDDLAction _act = PDDLAction(
        "testaction",
        std::vector<std::string> {"?x", "?y"},
        std::vector<PDDLLiteral> {PDDLLiteral(1, std::vector<unsigned int> {0}, true)},
        std::vector<PDDLLiteral> {PDDLLiteral(2, std::vector<unsigned int> {1}, true)}
    );
    PDDLActionInstance act1 = PDDLActionInstance(&_act, std::vector<unsigned int> {0, 1});
    PDDLActionInstance act2 = PDDLActionInstance(&_act, std::vector<unsigned int> {0, 1});
    actions.push_back(&act1);
    actions.push_back(&act2);
    // generate macro
    MacroGenerator macroGenerator = MacroGenerator();
    Macro m = macroGenerator.GenerateMacro(&actions);
    // expected stuff
    std::unordered_map<GroundedLiteral, bool> expectedPrecons ({
        {GroundedLiteral(1, std::vector<unsigned int> {0}), true}
    });
    std::unordered_map<GroundedLiteral, bool> expectedEffects ({
        {GroundedLiteral(2, std::vector<unsigned int> {1}), true}
    });
    REQUIRE(m.groundedAction.parameters == std::unordered_set<unsigned int> {0, 1});
    REQUIRE(m.groundedAction.preconditions == expectedPrecons);
    REQUIRE(m.groundedAction.effects == expectedEffects);
}