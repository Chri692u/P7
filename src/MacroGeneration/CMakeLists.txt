add_library(MacroGeneration "MacroGeneration.cpp")
target_sources(MacroGeneration
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/MacroGeneration.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/MacroGeneration.hh)
target_include_directories(MacroGeneration
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})