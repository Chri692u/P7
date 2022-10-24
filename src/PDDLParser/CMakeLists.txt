add_library(PDDLParser "action.cc" "domain.cc" "location.hh" "pddldriver.cc" "pddllex.yy.cc" "pddlparser.tab.cc" "position.hh" "predicate.cc" "problem.cc" "stack.hh")
target_include_directories(PDDLParser
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
