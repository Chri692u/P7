add_executable(Tests-SASCodeGenerator Test/SASCodeGenerator/SASCodeGenerator.cpp)
target_link_libraries(Tests-SASCodeGenerator 
    PRIVATE 
        Catch2::Catch2WithMain
        SASCodeGenerator
        SASParser)
catch_discover_tests(Tests-SASCodeGenerator)