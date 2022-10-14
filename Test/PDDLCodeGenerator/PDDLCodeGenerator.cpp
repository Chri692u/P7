#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../src/PDDLCodeGenerator/PDDLCodeGenerator.hh"
#include "../../src/PDDLCodeGenerator/PDDLDomainCodeGenerator.hh"
#include "../../src/PDDLCodeGenerator/PDDLProblemCodeGenerator.hh"

using namespace std;

const string TAG = "PDDLCodeGenerator ";
const string domainFile = "./TestFiles/gripper.pddl";
const string problemFile = "./TestFiles/gripper-4.pddl";

TEST_CASE(TAG + "PDDLDomainGenerator") {
    PDDLDriver driver;
    driver.parse(domainFile);
    Domain* driverDomain = driver.domain;
    PDDLDomain domain = PDDLDomain(driverDomain);
    PDDLDomainCodeGenerator PDDLDomainGen = PDDLDomainCodeGenerator();
    string domainString = PDDLDomainGen.GenerateDomainString(&domain);

    ofstream newfile ("domain.pddl", ofstream::out | ofstream::trunc);
    newfile << domainString;
    newfile.close();

    PDDLDriver driver2;
    driver2.parse("domain.pddl");
    Domain* driverGeneratedDomain = driver2.domain;
    PDDLDomain generatedDomain = PDDLDomain(driverDomain);
    REQUIRE(generatedDomain.requirements.size() == domain.requirements.size());
    REQUIRE(generatedDomain.predicates.size() == domain.predicates.size());
    REQUIRE(generatedDomain.actions.size() == domain.actions.size());
}

TEST_CASE(TAG + "PDDLProblemGenerator") {
    PDDLDriver driver;
    driver.parse(domainFile);
    driver.parse(problemFile);
    Domain* driverDomain = driver.domain;
    PDDLDomain domain = PDDLDomain(driverDomain);
    Problem* driverProblem = driver.problem;
    PDDLProblem problem = PDDLProblem(driverProblem, &domain);
    PDDLProblemCodeGenerator PDDLProblemGen = PDDLProblemCodeGenerator();
    string problemString = PDDLProblemGen.GenerateProblemString(&problem);

    ofstream newfile ("problem.pddl", ofstream::out | ofstream::trunc);
    newfile << problemString;
    newfile.close();

    PDDLDriver driver2;
    driver2.parse("problem.pddl");
    Problem* driverGeneratedProblem = driver2.problem;
    PDDLProblem generatedProblem = PDDLProblem(driverGeneratedProblem, &domain);
    REQUIRE(generatedProblem.name == problem.name);
    //REQUIRE(generatedProblem->_domain == problem->_domain);
    REQUIRE(generatedProblem.objects.size() == problem.objects.size());
    REQUIRE(generatedProblem.initState.state.size() == problem.initState.state.size());
    REQUIRE(generatedProblem.goalState.state.size() == problem.goalState.state.size());
}