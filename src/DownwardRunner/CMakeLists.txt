add_library(DownwardRunner "DownwardRunner.cpp")
target_sources(DownwardRunner
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/DownwardRunner.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/DownwardRunner.hh)
target_include_directories(DownwardRunner
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})