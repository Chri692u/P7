add_library(PDDLCodeGenerator "BasePDDLCodeGenerator.cpp" "PDDLCodeGenerator.cpp" "PDDLDomainCodeGenerator.cpp" "PDDLProblemCodeGenerator.cpp")
target_sources(PDDLCodeGenerator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/BasePDDLCodeGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PDDLCodeGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PDDLDomainCodeGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PDDLProblemCodeGenerator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BasePDDLCodeGenerator.hh
        ${CMAKE_CURRENT_LIST_DIR}/PDDLCodeGenerator.hh
        ${CMAKE_CURRENT_LIST_DIR}/PDDLDomainCodeGenerator.hh
        ${CMAKE_CURRENT_LIST_DIR}/PDDLProblemCodeGenerator.hh)
target_include_directories(PDDLCodeGenerator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})