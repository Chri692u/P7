#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../src/Config/Config.hh"
#include "../../src/DownwardRunner/DownwardRunner.hh"

using namespace std;

const string TAG = "DownwardRunner ";

TEST_CASE(TAG + "Run a legal domain"){
    DownwardRunner downward = DownwardRunner();
    downward.RunnerLogName = "./TestFiles/downwardLog_good";
    auto x = downward.ParseDownwardLog();
    REQUIRE(x == DownwardRunner::DownwardRunnerResult::FoundPlan);
}

TEST_CASE(TAG + "Run impossible domain"){
    DownwardRunner downward = DownwardRunner();
    downward.RunnerLogName = "./TestFiles/downwardLog_bad";
    auto x = downward.ParseDownwardLog();
    REQUIRE(x == DownwardRunner::DownwardRunnerResult::DidNotFindPlan);
}

TEST_CASE(TAG + "Run illegal domain"){
    DownwardRunner downward = DownwardRunner();
    downward.RunnerLogName = "./TestFiles/downwardLog_none";
    auto x = downward.ParseDownwardLog();
    REQUIRE(x == DownwardRunner::DownwardRunnerResult::None);
}
