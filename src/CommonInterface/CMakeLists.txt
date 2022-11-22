add_library(CommonInterface "CommonInterface.cpp")
target_sources(CommonInterface
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/CommonInterface.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/CommonInterface.hh)
target_include_directories(CommonInterface
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/PDDLParser
        ${CMAKE_SOURCE_DIR}/src/PlanGenerator)
target_link_libraries(CommonInterface
    PRIVATE
        PlanGenerator
        ConsoleHelper
        PDDLCodeGenerator)