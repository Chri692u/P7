add_library(MacroGrounder "MacroGrounder.cpp" )
target_sources(MacroGrounder
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/MacroGrounder.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/MacroGrounder.hh)
target_include_directories(MacroGrounder
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})