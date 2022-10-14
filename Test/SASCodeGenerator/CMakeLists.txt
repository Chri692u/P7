add_executable(Tests-SASCodeGenerator Test/SASCodeGenerator/SASCodeGenerator.cpp ${SOURCES})
target_link_libraries(Tests-SASCodeGenerator PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(Tests-SASCodeGenerator)