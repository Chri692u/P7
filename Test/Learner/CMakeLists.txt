add_executable(Tests-Learner Test/Learner/Learner.cpp)
target_link_libraries(Tests-Learner
    PRIVATE 
        Catch2::Catch2WithMain
        Config
        Learner
        PlanGenerator
        IntermediatePDDL
        SASParser
        DownwardRunner
        PDDLParser)

file(COPY Test/Learner/gripper DESTINATION ${CMAKE_BINARY_DIR})
catch_discover_tests(Tests-Learner)
