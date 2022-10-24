add_library(PlanValidator "PlanValidator.cpp")
target_sources(PlanValidator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/PlanValidator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/PlanValidator.hh)
target_include_directories(PlanValidator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
