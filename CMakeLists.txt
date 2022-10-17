cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)

project(P7 VERSION 0.1.0)
project(P7Lab VERSION 0.1.0)

# Add source to this project's executable.
set(SOURCES 
    # PDDL Parser
	"src/PDDLParser/action.cc" "src/PDDLParser/pddldriver.cc" "src/PDDLParser/domain.cc" "src/PDDLParser/pddllex.yy.cc" "src/PDDLParser/pddlparser.tab.cc" "src/PDDLParser/predicate.cc" "src/PDDLParser/problem.cc"
	# Config
	"src/Config/config.cpp"
	# Fast Downward
	"src/DownwardRunner/DownwardRunner.cpp"
	# SAS Parser
	"src/SASParser/SASParser.cpp"
	# Time Report
	"src/RunReport/RunReport.cpp"
	# PDDL Code Generator
	"src/PDDLCodeGenerator/PDDLCodeGenerator.cpp" "src/PDDLCodeGenerator/PDDLDomainCodeGenerator.cpp" "src/PDDLCodeGenerator/PDDLProblemCodeGenerator.cpp" "src/PDDLCodeGenerator/BasePDDLCodeGenerator.cpp" 
	# SAS Code Generator
	"src/SASCodeGenerator/SASCodeGenerator.cpp" 
	# File Verifier
	"src/FileVerifier/FileVerifier.cpp" 
	# Helpers
	"src/Helpers/StringHelper.cpp" "src/Helpers/FileHelper.cpp" 
	# Reformulators
	"src/Reformulators/SameOutputReformulator.cpp" "src/Reformulators/RandomWalkerReformulator.cpp"
	# Common Interface
	"src/CommonInterface/CommonInterface.cpp"
	# Plan Validator
	"src/PlanValidators/PlanValidator.cpp" 
    # PDDL Types
	"src/IntermediatePDDL/PDDLConverter.cpp" "src/IntermediatePDDL/PDDLAction.hh" "src/IntermediatePDDL/PDDLLiteral.hh" "src/IntermediatePDDL/PDDLDomain.hh" "src/IntermediatePDDL/PDDLPredicate.hh" "src/IntermediatePDDL/PDDLProblem.hh" "src/IntermediatePDDL/PDDLInstance.hh" "src/IntermediatePDDL/PDDLState.hh"
	# Walker
	"src/Walker/ActionGenerator.cpp" "src/Walker/Walker.cpp"
	## Heuristics
	"src/Walker/Heuristics/BaseHeuristics.hh" "src/Walker/Heuristics/RandomHeuristic.hh" "src/Walker/Heuristics/Contexts/BaseContext.hh" "src/Walker/Heuristics/Contexts/PDDLContext.hh"
	## Depth Functions
	"src/Walker/DepthFunctions/BaseDepthFunction.hh" "src/Walker/DepthFunctions/ObjectActionDepthFunction.hh" "src/Walker/DepthFunctions/ObjectActionDepthFunction.cpp" "src/Walker/DepthFunctions/ConstantDepthFunction.hh" "src/Walker/DepthFunctions/ConstantDepthFunction.cpp"
	# Width Functions
	"src/Walker/WidthFunctions/ConstantWidthFunction.cpp"
	# Path Checkers
	"src/PathCheckers/PathChecker.cpp"
	# Macros
	"src/MacroGeneration/MacroGeneration.cpp"

	# Something new ᓚᘏᗢ

)
add_executable (P7 "src/P7.cpp" ${SOURCES})
add_executable (P7Lab "src/P7Lab.cpp" ${SOURCES})
target_include_directories(P7 PRIVATE "PDDLParser")

file(COPY Data DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "runP7.py" DESTINATION ${CMAKE_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(Test/CMakeLists.txt)