#include <catch2/catch_test_macros.hpp>

#include "../../../src/Walker/DepthFunctions/ConstantDepthFunction.hh"

const std::string TAG = "ConstantDepthFunction ";

TEST_CASE(TAG + "SimpleTest") {
    std::vector<int> testCases = {1,2,10,75,1245623,0,1241};
    PDDLInstance emptyInstace(nullptr, nullptr);
    for (auto testCase : testCases) {
        BaseDepthFunction* function = new ConstantDepthFunction(testCase, emptyInstace);
        int expected = testCase;
        int actual = function->GetDepth();
        REQUIRE(expected == actual);
    }
}

TEST_CASE(TAG + "WithModifier") {
    double modifier = 0.5;
    std::vector<int> testCases = { 1,2,10,75,1245623,0,1241 };
    PDDLInstance emptyInstace(nullptr, nullptr);
    for (auto testCase : testCases) {
        BaseDepthFunction* function = new ConstantDepthFunction(testCase, emptyInstace, modifier);
        int expected = testCase * modifier;
        int actual = function->GetDepth();
        REQUIRE(expected == actual);
    }
}