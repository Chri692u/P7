#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_set>

#include "../../src/IntermediatePDDL/PDDLDomain.hh"
#include "../../src/PDDLParser/pddldriver.hh"

using namespace std;


const string TAG = "IntermediatePDDL ";

const string domainFile = "./TestFiles/gripper.pddl";
const string exDomainName = "gripper";
const vector<string> exDomainReq = {":strips", ":equality"};
const vector<string> exConditions = {"ROOM", "BALL", "GRIPPER", "at-lobby", "at-ball", "free", "carry"};
const vector<string> exActions = {"move", "pick-up", "drop"};
const vector<string> exArgs = {"?z", "?y", "?x"};

bool cmp(vector<string> as, vector<string> bs){
    bool acc = false;
    for(string a : as)
        for (string b : bs)
            acc = (a == b) ? true : false;

    return acc;
}

TEST_CASE(TAG + "PDDLDomain domain name") {
    PDDLDriver driver;
    driver.parse(domainFile);
    PDDLDomain *domain = new PDDLDomain(driver.domain);

    REQUIRE(domain->name == exDomainName);
}

TEST_CASE(TAG + "PDDLDomain requirements") {
    PDDLDriver driver;
    driver.parse(domainFile);
    PDDLDomain *domain = new PDDLDomain(driver.domain);

    REQUIRE(cmp(domain->requirements, exDomainReq));
}

TEST_CASE(TAG + "PDDLDomain preconditions"){
    PDDLDriver driver;
    driver.parse(domainFile);
    PDDLDomain *domain = new PDDLDomain(driver.domain);

    auto preds = domain->predicates;
    vector<string> predStrings;

    for (auto p : preds)
        predStrings.push_back(p.name);

    REQUIRE(cmp(predStrings, exConditions));
}

TEST_CASE(TAG + "PDDLDomain action names"){
    PDDLDriver driver;
    driver.parse(domainFile);
    PDDLDomain *domain = new PDDLDomain(driver.domain);

    auto acts = domain->actions;
    vector<string> actStrings;

    for (auto a : acts)
	    actStrings.push_back(a.name);

    REQUIRE(cmp(actStrings, exActions));
}

TEST_CASE(TAG + "PDDLDomain arguments"){
    PDDLDriver driver;
    driver.parse(domainFile);
    PDDLDomain *domain = new PDDLDomain(driver.domain);

    auto acts = domain->actions;
    unordered_set<string> args;
	vector<string> argString;

    for (auto a : acts)
        for (auto arg : a.parameters)
            args.insert(arg.name);

	for (string a : args)
		argString.push_back(a);
    
    REQUIRE(cmp(argString, exArgs));
}