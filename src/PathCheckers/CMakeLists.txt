add_library(PathChecker "PathChecker.cpp")
target_sources(PathChecker
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/PathChecker.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/PathChecker.hh)
target_include_directories(PathChecker
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})