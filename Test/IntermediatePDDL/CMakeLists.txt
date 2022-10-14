add_executable(Tests-IntermediatePDDL Test/IntermediatePDDL/IntermediatePDDL.cpp ${SOURCES})
target_link_libraries(Tests-IntermediatePDDL PRIVATE Catch2::Catch2WithMain)

file(COPY Test/IntermediatePDDL/TestFiles DESTINATION ${CMAKE_BINARY_DIR})

catch_discover_tests(Tests-IntermediatePDDL)
