add_executable(Tests-EntanglementFinder Test/EntanglementFinder/EntanglementFinder.cpp)
target_link_libraries(Tests-EntanglementFinder 
    PRIVATE 
        Catch2::Catch2WithMain
        EntanglementFinder
        IntermediatePDDL
        ProgressBarHelper)

catch_discover_tests(Tests-EntanglementFinder)
