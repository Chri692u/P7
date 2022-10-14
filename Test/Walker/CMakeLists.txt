add_executable(Tests-Walker Test/Walker/CMakeLists.txt ${SOURCES})
target_link_libraries(Tests-Walker PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(Tests-Walker)
