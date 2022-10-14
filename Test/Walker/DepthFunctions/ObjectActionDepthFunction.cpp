#include <catch2/catch_test_macros.hpp>

#include "../../../src/Walker/DepthFunctions/ObjectActionDepthFunction.hh"

const std::string TAG = "ObjectActionDepthFunction ";

TEST_CASE(TAG + "SimpleTest") {
    // Pairs of how many Actions (first) and Objects (second) to make.
    std::vector<std::pair<int, int>> testCases = { 
        {1,1},
        {10,1},
        {2,5},
        {10,10}
    };

    for (auto pair : testCases) {
        int expected = pair.first * pair.second;
        PDDLDomain newDomain;
        PDDLProblem newProblem;

        for(int i = 0; i < pair.first; i++)
            newDomain.actions.push_back(PDDLAction());

        for (int i = 0; i < pair.second; i++)
            newProblem.objects.push_back("ObjName");

        REQUIRE(pair.first == newDomain.actions.size());
        REQUIRE(pair.second == newProblem.objects.size());

        PDDLInstance emptyInstace(&newDomain, &newProblem);
        BaseDepthFunction* function = new ObjectActionDepthFunction(emptyInstace);
        int actual = function->GetDepth();
        REQUIRE(expected == actual);
    }
}

TEST_CASE(TAG + "WithModifier") {
    double modifier = 0.5;
    // Pairs of how many Actions (first) and Objects (second) to make.
    std::vector<std::pair<int, int>> testCases = {
        {1,1},
        {10,1},
        {2,5},
        {10,10}
    };

    for (auto pair : testCases) {
        int expected = (pair.first * pair.second) * modifier;
        PDDLDomain newDomain;
        PDDLProblem newProblem;

        for (int i = 0; i < pair.first; i++)
            newDomain.actions.push_back(PDDLAction());

        for (int i = 0; i < pair.second; i++)
            newProblem.objects.push_back("ObjName");

        REQUIRE(pair.first == newDomain.actions.size());
        REQUIRE(pair.second == newProblem.objects.size());

        PDDLInstance emptyInstace(&newDomain, &newProblem);
        BaseDepthFunction* function = new ObjectActionDepthFunction(emptyInstace, modifier);
        int actual = function->GetDepth();
        REQUIRE(expected == actual);
    }
}