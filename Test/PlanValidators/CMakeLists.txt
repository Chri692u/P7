add_executable(Tests-PlanValidator Test/PlanValidators/PlanValidator.cpp ${SOURCES})
target_link_libraries(Tests-PlanValidator PRIVATE Catch2::Catch2WithMain)

file(COPY Test/PlanValidators/TestFiles DESTINATION ${CMAKE_BINARY_DIR})

catch_discover_tests(Tests-PlanValidator)
