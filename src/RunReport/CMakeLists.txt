add_library(RunReport "RunReport.cpp")
target_sources(RunReport
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/RunReport.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/RunReport.hh)
target_include_directories(RunReport
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})