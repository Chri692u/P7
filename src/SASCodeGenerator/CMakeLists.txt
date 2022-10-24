add_library(SASCodeGenerator "SASCodeGenerator.cpp")
target_sources(SASCodeGenerator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/SASCodeGenerator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/SASCodeGenerator.hh)
target_include_directories(SASCodeGenerator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})