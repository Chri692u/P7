add_library(ConsoleHelper "ConsoleHelper.cpp")
target_sources(ConsoleHelper
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ConsoleHelper.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ConsoleHelper.hh)
target_include_directories(ConsoleHelper
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

add_library(FileHelper "FileHelper.cpp")
target_sources(FileHelper
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/FileHelper.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/FileHelper.hh)
target_include_directories(FileHelper
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

add_library(StringHelper "StringHelper.cpp")
target_sources(StringHelper
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/StringHelper.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/StringHelper.hh)
target_include_directories(StringHelper
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})