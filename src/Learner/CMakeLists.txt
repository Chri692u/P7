add_library(Learner "Learner.cpp")
target_sources(Learner
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Learner.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Learner.hh)
target_include_directories(Learner
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})