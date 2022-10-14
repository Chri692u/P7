add_executable(Tests-Helpers Test/Helpers/StringHelper.cpp ${SOURCES})
target_link_libraries(Tests-Helpers PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(Tests-Helpers)
