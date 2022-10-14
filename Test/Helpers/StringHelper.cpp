#include <catch2/catch_test_macros.hpp>

#include "../../src/Helpers/StringHelper.hh"

using namespace std;
const string TAG = "StringHelper ";

#pragma region RemoveCharacter

TEST_CASE(TAG + "RemoveCharacter_None_Ptr") {
    string line = "a b c d/(2";
    StringHelper::RemoveCharacter(&line, 'q');
    REQUIRE(line == line);
}

TEST_CASE(TAG + "RemoveCharacter_Single1_Ptr") {
    string line = "a b c d/(2";
    string expectedLine = " b c d/(2";
    StringHelper::RemoveCharacter(&line, 'a');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_Single2_Ptr") {
    string line = "a b c d/(2";
    string expectedLine = "abcd/(2";
    StringHelper::RemoveCharacter(&line, ' ');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_Single3_Ptr") {
    string line = "a b c d/(2";
    string expectedLine = "a b  d/(2";
    StringHelper::RemoveCharacter(&line, 'c');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_Multiple1_Ptr") {
    string line = "a b c d/(2";
    string expectedLine = "   d/(2";
    StringHelper::RemoveCharacter(&line, 'a');
    StringHelper::RemoveCharacter(&line, 'b');
    StringHelper::RemoveCharacter(&line, 'c');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_Multiple2_Ptr") {
    string line = "a b c d/(2";
    string expectedLine = "d/(2";
    StringHelper::RemoveCharacter(&line, 'a');
    StringHelper::RemoveCharacter(&line, 'b');
    StringHelper::RemoveCharacter(&line, 'c');
    StringHelper::RemoveCharacter(&line, ' ');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_None_Ins") {
    string line = "a b c d/(2";
    line = StringHelper::RemoveCharacter(line, 'q');
    REQUIRE(line == line);
}

TEST_CASE(TAG + "RemoveCharacter_Single1_Ins") {
    string line = "a b c d/(2";
    string expectedLine = " b c d/(2";
    line = StringHelper::RemoveCharacter(line, 'a');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_Single2_Ins") {
    string line = "a b c d/(2";
    string expectedLine = "abcd/(2";
    line = StringHelper::RemoveCharacter(line, ' ');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_Single3_Ins") {
    string line = "a b c d/(2";
    string expectedLine = "a b  d/(2";
    line = StringHelper::RemoveCharacter(line, 'c');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_Multiple1_Ins") {
    string line = "a b c d/(2";
    string expectedLine = "   d/(2";
    line = StringHelper::RemoveCharacter(line, 'a');
    line = StringHelper::RemoveCharacter(line, 'b');
    line = StringHelper::RemoveCharacter(line, 'c');
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "RemoveCharacter_Multiple2_Ins") {
    string line = "a b c d/(2";
    string expectedLine = "d/(2";
    line = StringHelper::RemoveCharacter(line, 'a');
    line = StringHelper::RemoveCharacter(line, 'b');
    line = StringHelper::RemoveCharacter(line, 'c');
    line = StringHelper::RemoveCharacter(line, ' ');
    REQUIRE(line == expectedLine);
}

#pragma endregion

TEST_CASE(TAG + "Trim_None1_Ins") {
    string line = "text text";
    line = StringHelper::Trim(line);
    REQUIRE(line == line);
}

TEST_CASE(TAG + "Trim_Single1_Ins") {
    string line = " text text ";
    string expectedLine = "text text";
    line = StringHelper::Trim(line);
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "Trim_Single2_Ins") {
    string line = "      text text ";
    string expectedLine = "text text";
    line = StringHelper::Trim(line);
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "Trim_Single3_Ins") {
    string line = "      text text                    ";
    string expectedLine = "text text";
    line = StringHelper::Trim(line);
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "Trim_None1_Ptr") {
    string line = "text text";
    StringHelper::Trim(&line);
    REQUIRE(line == line);
}

TEST_CASE(TAG + "Trim_Single1_Ptr") {
    string line = " text text ";
    string expectedLine = "text text";
    StringHelper::Trim(&line);
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "Trim_Single2_Ptr") {
    string line = "      text text ";
    string expectedLine = "text text";
    StringHelper::Trim(&line);
    REQUIRE(line == expectedLine);
}

TEST_CASE(TAG + "Trim_Single3_Ptr") {
    string line = "      text text                    ";
    string expectedLine = "text text";
    StringHelper::Trim(&line);
    REQUIRE(line == expectedLine);
}
