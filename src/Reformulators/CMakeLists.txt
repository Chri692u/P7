add_library(Reformulator "BaseReformulator.hh" "WalkerReformulator.cpp" "SameOutputReformulator.cpp")
target_sources(Reformulator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/WalkerReformulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SameOutputReformulator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BaseReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/WalkerReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/SameOutputReformulator.hh)
target_include_directories(Reformulator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})