#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "../../src/SASCodeGenerator/SASCodeGenerator.hh"

using namespace std;

const string tag = "SASCodeGenerator: ";

bool checkTranslation(string test, string targetFile){
    //Generator and parser
    SASCodeGenerator gen;
    SASParser parser;

    //Get plan and generate file
    SASPlan plan = parser.Parse(test);
    gen.GenerateCode(plan, targetFile);
    string fcontent = gen.GenerateCodeString(plan, targetFile);
    return test == fcontent;
}

TEST_CASE(tag + "Check generation"){
    //Test setup
    string test = "(task p1)\n; cost = 1 (general cost)\n";
    string fname = "./Example";
    //Assertion
    REQUIRE(checkTranslation(test, fname));
}

TEST_CASE(tag + "Multiparameters"){
    //Test setup
    string test = "(task p1 p2 p3 p4 p5)\n; cost = 1 (general cost)\n";
    string fname = "./Example";
    //Assertion
    REQUIRE(checkTranslation(test, fname));
}

TEST_CASE(tag + "Missing semicolon"){
    //Test setup
    string test = "(task p1)\n cost = 1 (general cost)\n";
    string fname = "./Example";
    //Assertion
    REQUIRE(!checkTranslation(test, fname));
}

TEST_CASE(tag + "Illegal program 1"){
    //Test setup
    string test = ";cost = 1 (general cost)\n (task p1)";
    string fname = "./Example";
    //Assertion
    REQUIRE(!checkTranslation(test, fname));
}

TEST_CASE(tag + "Illegal program 2"){
    //Test setup
    string test = "(task p1 p2 p3)\n";
    string fname = "./Example";
    //Assertion
    REQUIRE(!checkTranslation(test, fname));
}