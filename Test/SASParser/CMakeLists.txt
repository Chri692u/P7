add_executable(Tests-SASParser Test/SASParser/SASParser.cpp)
target_link_libraries(Tests-SASParser 
    PRIVATE 
        Catch2::Catch2WithMain
        SASParser
        StringHelper)

catch_discover_tests(Tests-SASParser)
