add_library(FileVerifier "FileVerifier.cpp")
target_sources(Config
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/FileVerifier.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/FileVerifier.hh)
target_include_directories(FileVerifier
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})