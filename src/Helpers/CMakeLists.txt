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

add_library(Hashes "Hashes.hh")
target_sources(Hashes
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Hashes.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Hashes.hh)
target_include_directories(Hashes
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
        
add_library(ProgressBarHelper "ProgressBarHelper.cpp")
target_sources(ProgressBarHelper
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ProgressBarHelper.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ProgressBarHelper.hh)
target_include_directories(ProgressBarHelper
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(ProgressBarHelper
    PRIVATE
        ConsoleHelper)
