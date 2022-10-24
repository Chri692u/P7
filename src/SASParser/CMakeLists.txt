add_library(SASParser "SASParser.cpp")
target_sources(SASParser
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/SASParser.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/SASParser.hh)
target_include_directories(SASParser
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(SASParser
    PRIVATE
        StringHelper)