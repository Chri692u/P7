add_library(Config "Config.cpp")
target_sources(Config
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Config.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Config.hh)
target_include_directories(Config
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})