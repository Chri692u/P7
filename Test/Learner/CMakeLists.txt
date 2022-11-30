add_executable(Tests-Learner Test/Learner/Learner.cpp)
target_link_libraries(Tests-Learner
    PRIVATE 
        Catch2::Catch2WithMain
        Learner
        PlanGenerator)

catch_discover_tests(Tests-Learner)
