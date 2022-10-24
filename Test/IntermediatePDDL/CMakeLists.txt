add_executable(Tests-IntermediatePDDL Test/IntermediatePDDL/IntermediatePDDL.cpp)
target_link_libraries(Tests-IntermediatePDDL 
    PRIVATE 
        Catch2::Catch2WithMain
        IntermediatePDDL
        PDDLParser)

file(COPY Test/IntermediatePDDL/TestFiles DESTINATION ${CMAKE_BINARY_DIR})

catch_discover_tests(Tests-IntermediatePDDL)
