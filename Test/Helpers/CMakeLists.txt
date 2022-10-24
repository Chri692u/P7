add_executable(Tests-Helpers Test/Helpers/StringHelper.cpp)
target_link_libraries(Tests-Helpers 
    PRIVATE 
        Catch2::Catch2WithMain
        StringHelper)

catch_discover_tests(Tests-Helpers)
