add_library(Walker "Walker.cpp")
target_sources(Walker
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Walker.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Walker.hpp)
target_include_directories(Walker
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(Walker
    PRIVATE
        IntermediatePDDL)

add_library(ActionGenerator "ActionGenerator.cpp")
target_sources(ActionGenerator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ActionGenerator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ActionGenerator.hpp)
target_include_directories(ActionGenerator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})