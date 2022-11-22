add_library(PlanGenerator "PlanGenerator.cpp")
target_sources(PlanGenerator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/PlanGenerator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/PlanGenerator.hh)
target_include_directories(PlanGenerator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})