add_executable(Tests-DepthFunctions Test/Walker/DepthFunctions/ConstantDepthFunction.cpp Test/Walker/DepthFunctions/ObjectActionDepthFunction.cpp ${SOURCES})
target_link_libraries(Tests-DepthFunctions PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(Tests-DepthFunctions)
