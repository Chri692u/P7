#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "../../src/EntanglementFinder/EntanglementFinder.hh"
#include "../../src/Walker/Walker.hpp"

using namespace std;

const std::string TAG = "EntanglementFinder ";

#pragma region Can_FindLargeOccurance

TEST_CASE(TAG + "Can_FindLargeOccurance_1") {
    PDDLAction constantAction;
    PDDLActionInstance constantInstance(&constantAction, {});
    vector<Path> paths = { 
        Path({ constantInstance,constantInstance,constantInstance,constantInstance }),
        Path({ constantInstance,constantInstance,constantInstance,constantInstance }) };

    EntanglementFinder finder(4, -1, 2, 0);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
    auto firstObject = *result.begin();
    REQUIRE(firstObject.second.Chain.size() == 4);
    REQUIRE(firstObject.second.Occurance == 2);
}

TEST_CASE(TAG + "Can_FindLargeOccurance_2") {
    PDDLAction constantAction1("a");
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2("b");
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }) };

    EntanglementFinder finder(4,-1,2,1);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
    auto firstObject = *result.begin();
    REQUIRE(firstObject.second.Chain.size() == 4);
    REQUIRE(firstObject.second.Occurance == 4);
}

TEST_CASE(TAG + "Can_FindLargeOccurance_3") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance2,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }) };

    EntanglementFinder finder(4, -1, 2, 0);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 2);
    for(auto i = result.begin(); i != result.end(); i++)
        REQUIRE((*i).second.Chain.size() == 4);
}

TEST_CASE(TAG + "Can_FindLargeOccurance_Uneven_1") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance2,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance2,constantInstance1 }),
        Path({ constantInstance2,constantInstance2,constantInstance1 }) };

    EntanglementFinder finder(4, -1, 2, 0);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
}

#pragma endregion

#pragma region Cant_FindLargeOccurance

TEST_CASE(TAG + "Cant_FindLargeOccurance_IfNotThere_1") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1 }) };

    EntanglementFinder finder(4);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 0);
}

TEST_CASE(TAG + "Cant_FindLargeOccurance_IfNotThere_2") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance1,constantInstance1,constantInstance2 }),
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance1,constantInstance1,constantInstance1 }) };

    EntanglementFinder finder(4);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 0);
}

#pragma endregion

#pragma region Can_FindMediumOccurance

TEST_CASE(TAG + "Can_FindMediumOccurance_1") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        //      Should find this as an occurance
        //     | ------------------------------- |
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1 }) };

    EntanglementFinder finder(2,-1,2,1);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
}

TEST_CASE(TAG + "Can_FindMediumOccurance_Uneven_1") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        //      Should find this as an occurance
        //     | ------------------------------- |
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1, constantInstance1 }) };

    EntanglementFinder finder(2, -1, 2, 1);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
}

TEST_CASE(TAG + "Can_FindMediumOccurance_Uneven_2") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        //      Should find this as an occurance
        //     | ------------------------------- |
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1, constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1 }) };

    EntanglementFinder finder(2, -1, 2, 1);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
}

TEST_CASE(TAG + "Can_FindMediumOccurance_Uneven_3") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        //      Should find this as an occurance
        //     | ------------------------------- |
        Path({ constantInstance1,constantInstance1 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1 }) };

    EntanglementFinder finder(2, -1, 2, 1);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 1);
}

#pragma endregion

#pragma region Cant_FindMediumOccurance

TEST_CASE(TAG + "Cant_FindMediumOccurance_IfNotThere") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});
    PDDLAction constantAction3;
    PDDLActionInstance constantInstance3(&constantAction3, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance2,constantInstance2 }),
        Path({ constantInstance3,constantInstance3,constantInstance3 }) };

    EntanglementFinder finder(2, -1, 2, 1);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 0);
}

TEST_CASE(TAG + "Cant_FindMediumOccurance_IfNotThere_Uneven") {
    PDDLAction constantAction1;
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2;
    PDDLActionInstance constantInstance2(&constantAction2, {});
    PDDLAction constantAction3;
    PDDLActionInstance constantInstance3(&constantAction3, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance1,constantInstance1 }),
        Path({ constantInstance2 }),
        Path({ constantInstance3,constantInstance3 }) };

    EntanglementFinder finder(2, -1, 2, 1);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 0);
}

#pragma endregion

#pragma region Can_FindSmallOccurance

TEST_CASE(TAG + "Can_FindSmallOccurance_1") {
    PDDLAction constantAction1("a");
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2("b");
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        //      Should find this as an occurance
        //     | ------------------------------- |
        Path({ constantInstance1,constantInstance1,constantInstance2,constantInstance1, constantInstance1, constantInstance2 }),
        Path({ constantInstance1,constantInstance2,constantInstance1,constantInstance1, constantInstance1, constantInstance1 }) };

    EntanglementFinder finder(2, -1, 2, 1);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 3);
}

#pragma endregion

#pragma region Cant_FindSmallOccurance

TEST_CASE(TAG + "Cant_FindSmallOccurance_1") {
    PDDLAction constantAction1("a");
    PDDLActionInstance constantInstance1(&constantAction1, {});
    PDDLAction constantAction2("b");
    PDDLActionInstance constantInstance2(&constantAction2, {});

    vector<Path> paths = {
        Path({ constantInstance1,constantInstance1 }),
        Path({ constantInstance2,constantInstance2 }) };

    EntanglementFinder finder(2, -1, 2, 1);
    auto result = finder.FindEntangledCandidates(&paths);
    REQUIRE(result.size() == 0);
}

#pragma endregion

