#include <catch2/catch_test_macros.hpp>

#include "../../src/Walker/Walker.hpp"

const string TAG = "Walker ";

PDDLInstance GenerateInstance() {
    PDDLDomain* domain = new PDDLDomain();
    domain->name = "test domain";
    //domain.typeDict = std::unordered_map<std::string, PDDLType*>{
    //    ("type1", nullptr),
    //    ("type2", nullptr)
    //};
    domain->predicates = std::vector<PDDLPredicate>{
        PDDLPredicate("predicate1", std::vector<PDDLArg>{
            PDDLArg(0, "arg1", nullptr),
            PDDLArg(1, "arg2", nullptr)
        })
    };
    domain->requirements = std::vector<std::string>{
        "r1",
        "r2"
    };
    domain->actions = std::vector<PDDLAction>{
        PDDLAction("action1", 
        std::vector<PDDLArg>{
            PDDLArg(0, "arg1", nullptr),
            PDDLArg(1, "arg2", nullptr)
        },
        std::vector<PDDLLiteral>{
            PDDLLiteral(PDDLPredicate("p1", 
            std::vector<PDDLArg>{PDDLArg(0, "?x", nullptr)}), true)
        },
        std::vector<PDDLLiteral>{
            PDDLLiteral(PDDLPredicate("p1", 
            std::vector<PDDLArg>{PDDLArg(0, "?x", nullptr)}), false)
        })
    };
    return PDDLInstance(domain, nullptr);
}

TEST_CASE(TAG + "Walk") {
    PDDLInstance instance = GenerateInstance();
    ActionGenerator AG = ActionGenerator(instance.domain);
    //auto actions = AG.GenerateActions()
    free(instance.domain);
    free(instance.problem);
}
