add_library(Reformulator "BaseReformulator.hh" "RandomWalkerReformulator.cpp" "SameOutputReformulator.cpp")
target_sources(Reformulator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/RandomWalkerReformulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SameOutputReformulator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BaseReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/RandomWalkerReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/SameOutputReformulator.hh)
target_include_directories(Reformulator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})