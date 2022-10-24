#include <catch2/catch_test_macros.hpp>

#include "../../src/IntermediatePDDL/PDDLInstance.hh"
#include "../../src/Walker/ActionGenerator.hpp"

const std::string TAG = "ActionGenerator ";

#pragma region Iterate

std::vector<std::unordered_set<unsigned int>> GetCandidateObjectsPlaceholder(const unsigned int setCount, const unsigned int setSize) {
    std::vector<std::unordered_set<unsigned int>> candidateObjects;
    candidateObjects.reserve(setCount);
    for (int i = 0; i < setCount; i++) {
        std::unordered_set<unsigned int> tempSet;
        tempSet.reserve(setSize);
        for (int t = 0; t < setSize; t++)
            tempSet.emplace(t);
        candidateObjects.push_back(tempSet);
    }
    return candidateObjects;
}

std::vector<std::unordered_set<unsigned int>::iterator> GetIterators(std::vector<std::unordered_set<unsigned int>> &candidateObjects) {
    std::vector<std::unordered_set<unsigned int>::iterator> iterators;
    iterators.reserve(candidateObjects.size());
    for (int i = 0; i < candidateObjects.size(); i++)
        iterators.push_back(candidateObjects.at(i).begin());
    return iterators;
}

// static bool Iterate(std::vector<std::unordered_set<unsigned int>::iterator> *iteration, std::vector<std::unordered_set<unsigned int>> *candidateObjects);
TEST_CASE(TAG + "Iterate"){
    SECTION("Single Iteration") {
        auto candidateObjects = GetCandidateObjectsPlaceholder(2, 2);
        auto iteration = GetIterators(candidateObjects);
        REQUIRE(2 == iteration.size());
        std::vector<unsigned int> before;
        for (int i = 0; i < iteration.size(); i++)
            before.push_back(*iteration.at(i));
        REQUIRE(ActionGenerator::Iterate(&iteration, &candidateObjects));
        std::vector<unsigned int> after;
        for (int i = 0; i < iteration.size(); i++)
            after.push_back(*iteration.at(i));
        REQUIRE(before.at(0) != after.at(0));
        REQUIRE(before.at(1) == after.at(1));
    }

    SECTION("Overflow") {
        auto candidateObjects = GetCandidateObjectsPlaceholder(2, 2);
        auto iteration = GetIterators(candidateObjects);
        REQUIRE(2 == iteration.size());
        std::vector<unsigned int> before;
        for (int i = 0; i < iteration.size(); i++)
            before.push_back(*iteration.at(i));
        for (int i = 0; i < 2; i++)
            REQUIRE(ActionGenerator::Iterate(&iteration, &candidateObjects));
        std::vector<unsigned int> after;
        for (int i = 0; i < iteration.size(); i++)
            after.push_back(*iteration.at(i));
        REQUIRE(before.at(1) != after.at(1));
        REQUIRE(before.at(0) == after.at(0));
    }

    SECTION("End") {
        auto candidateObjects = GetCandidateObjectsPlaceholder(2, 2);
        auto iteration = GetIterators(candidateObjects);
        REQUIRE(2 == iteration.size());
        for (int i = 0; i < 4; i++) {
            if (i != 3)
                REQUIRE(ActionGenerator::Iterate(&iteration, &candidateObjects));
            else
                REQUIRE(!ActionGenerator::Iterate(&iteration, &candidateObjects));
        }
    }
}

#pragma endregion Iterate
#pragma region GenerateActions

PDDLDomain GenerateDomain(std::vector<PDDLAction> actions = std::vector<PDDLAction>()) {
    return PDDLDomain("Test",
    std::vector<std::string>{},
    std::vector<PDDLPredicate>{
        PDDLPredicate("=", 0),
        PDDLPredicate("P1", 1),
        PDDLPredicate("P2", 2),
        PDDLPredicate("P3", 3)
    },
    std::unordered_map<std::string, unsigned int> {
        {"=", 0},
        {"P1", 1},
        {"P2", 2},
        {"P3", 3}
    },
    actions);
}

PDDLProblem GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>> unaryFacts = std::unordered_map<unsigned int, std::unordered_set<unsigned int>> {}, std::unordered_map<unsigned int, std::vector<MultiFact>> multiFacts = std::unordered_map<unsigned int, std::vector<MultiFact>> {}, 
PDDLDomain *domain = nullptr, std::vector<std::string> objects = std::vector<std::string>()) {
    return PDDLProblem("Test", 
    domain, 
    objects, 
    std::unordered_map<std::string, unsigned int>{}, 
    PDDLState(unaryFacts, multiFacts), 
    PDDLState(unaryFacts, multiFacts));
}

TEST_CASE(TAG + "GenerateActions Empty") {
    PDDLInstance instance = PDDLInstance(new PDDLDomain(), new PDDLProblem());
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&instance.problem->initState);
    REQUIRE(actions.size() == 0);
    free(instance.domain);
    free(instance.problem);
}

TEST_CASE(TAG + "GenerateActions Unary - 1 Legal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(1, std::vector<unsigned int>{ 0 }, true)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        { 1, { 0 } }
    }, std::unordered_map<unsigned int, std::vector<MultiFact>>{

    }, &domain,
    std::vector<std::string> {
        "O1"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
}

TEST_CASE(TAG + "GenerateActions Unary - 0 Legal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(1, std::vector<unsigned int>{ 0 }, false)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        { 1, { 0 } }
    }, std::unordered_map<unsigned int, std::vector<MultiFact>>{

    }, &domain,
    std::vector<std::string> {
        "O1"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(0 == actions.size());
}

TEST_CASE(TAG + "GenerateActions Equal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x", "?y"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(0, std::vector<unsigned int>{ 0, 1 }, true)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        
    }, std::unordered_map<unsigned int, std::vector<MultiFact>>{

    }, &domain,
    std::vector<std::string> {
        "O1", "O2", "O3"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(3 == actions.size());
}

TEST_CASE(TAG + "GenerateActions Not Equal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x", "?y"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(0, std::vector<unsigned int>{ 0, 1 }, false)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        
    }, std::unordered_map<unsigned int, std::vector<MultiFact>>{

    }, &domain,
    std::vector<std::string> {
        "O1", "O2", "O3"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(6 == actions.size());
}

TEST_CASE(TAG + "GenerateActions Multi - 1 Legal") {
    PDDLDomain domain = GenerateDomain(std::vector<PDDLAction>{
        PDDLAction("Action 1", 
        {"?x", "?y"}, 
        std::vector<PDDLLiteral>{
            PDDLLiteral(2, std::vector<unsigned int>{ 0, 1 }, true)
        },
        std::vector<PDDLLiteral>{})
    });
    PDDLProblem problem = GenerateProblem(std::unordered_map<unsigned int, std::unordered_set<unsigned int>>{
        
    }, std::unordered_map<unsigned int, std::vector<MultiFact>>{
        { 2, { MultiFact({0, 1} )} }
    }, &domain,
    std::vector<std::string> {
        "O1", "O2", "O3", "O4"
    });

    PDDLInstance instance = PDDLInstance(&domain, &problem);
    ActionGenerator AG = ActionGenerator(instance.domain, instance.problem);
    std::vector<PDDLActionInstance> actions = AG.GenerateActions(&(instance.problem->initState));
    REQUIRE(1 == actions.size());
}

#pragma endregion GenerateActions
