find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main

include(CTest)
include(Catch)
#set(CMAKE_CTEST_ARGUMENTS "--verbose")

# Tests
include(Test/SASParser/CMakeLists.txt)
include(Test/SASCodeGenerator/CMakeLists.txt)
include(Test/PDDLCodeGenerator/CMakeLists.txt)
include(Test/PDDLParser/CMakeLists.txt)
include(Test/Walker/CMakeLists.txt)
include(Test/IntermediatePDDL/CMakeLists.txt)
include(Test/PlanValidators/CMakeLists.txt)
include(Test/Helpers/CMakeLists.txt)
include(Test/DownwardRunner/CMakeLists.txt)
include(Test/EntanglementFinder/CMakeLists.txt)
include(Test/MacroGenerator/CMakeLists.txt)
include(Test/Learner/CMakeLists.txt)

add_executable(Test-All 
	"Test/PDDLCodeGenerator/PDDLCodeGenerator.cpp"
	"Test/PDDLParser/PDDLParser.cpp"
	"Test/IntermediatePDDL/IntermediatePDDL.cpp"
	"Test/SASParser/SASParser.cpp"
	"Test/SASCodeGenerator/SASCodeGenerator.cpp"
	"Test/Walker/ActionGenerator.cpp"
	"Test/Walker/Walker.cpp"
	"Test/PlanValidators/PlanValidator.cpp"
	"Test/Helpers/StringHelper.cpp"
	"Test/EntanglementFinder/EntanglementFinder.cpp"
	"Test/EntanglementFinder/Hashes.cpp"
	"Test/DownwardRunner/DownwardRunner.cpp"
    "Test/MacroGenerator/MacroGenerator.cpp"
    "Test/Learner/Learner.cpp")
target_link_libraries(Test-All 
	PRIVATE 
		Catch2::Catch2WithMain
		RunReport
        Config
        StringHelper
        ConsoleHelper
        FileVerifier
        PathChecker
        Learner
        PDDLCodeGenerator
        CommonInterface
        PlanValidator
        Reformulator
        SASParser
        SASCodeGenerator
        PDDLParser
        IntermediatePDDL
        PathChecker
        DownwardRunner
        FileHelper
        EntanglementFinder
        Walker
        ActionGenerator
        MacroGenerator)