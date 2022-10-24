add_executable(Tests-DownwardRunner Test/DownwardRunner/DownwardRunner.cpp)
target_link_libraries(Tests-DownwardRunner 
    PRIVATE 
        Catch2::Catch2WithMain
        DownwardRunner)

file(COPY Test/DownwardRunner/TestFiles DESTINATION ${CMAKE_BINARY_DIR})

catch_discover_tests(Tests-DownwardRunner)
