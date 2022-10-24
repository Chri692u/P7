add_executable(Tests-ActionGenerator Test/Walker/ActionGenerator.cpp)
target_link_libraries(Tests-ActionGenerator 
    PRIVATE 
        Catch2::Catch2WithMain
        ActionGenerator
        IntermediatePDDL)

catch_discover_tests(Tests-ActionGenerator)


add_executable(Tests-Walker Test/Walker/Walker.cpp)
target_link_libraries(Tests-Walker 
    PRIVATE 
        Catch2::Catch2WithMain
        Walker
        IntermediatePDDL
        ActionGenerator)

catch_discover_tests(Tests-Walker)

