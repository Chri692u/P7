add_library(WidthFunction "BaseWidthFunction.hh" "ConstantWidthFunction.cpp" "TimeWidthFunction.cpp")
target_sources(WidthFunction
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ConstantWidthFunction.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TimeWidthFunction.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BaseWidthFunction.hh
        ${CMAKE_CURRENT_LIST_DIR}/ConstantWidthFunction.hh
        ${CMAKE_CURRENT_LIST_DIR}/TimeWidthFunction.hh)
target_include_directories(WidthFunction
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_directories(WidthFunction PRIVATE ${PROJECT_SOURCE_DIR}/src/IntermediatePDDL/)