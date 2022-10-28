add_executable(Tests-MacroGeneration Test/MacroGeneration/MacroGeneration.cpp)
target_link_libraries(Tests-MacroGeneration 
    PRIVATE 
        Catch2::Catch2WithMain
        MacroGeneration
        IntermediatePDDL)


catch_discover_tests(Tests-MacroGeneration)