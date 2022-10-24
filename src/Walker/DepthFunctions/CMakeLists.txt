add_library(DepthFunction "BaseDepthFunction.hh" "ConstantDepthFunction.cpp" "ObjectActionDepthFunction.cpp")
target_sources(DepthFunction
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ConstantDepthFunction.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ObjectActionDepthFunction.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BaseDepthFunction.hh
        ${CMAKE_CURRENT_LIST_DIR}/ConstantDepthFunction.hh
        ${CMAKE_CURRENT_LIST_DIR}/ObjectActionDepthFunction.hh)
target_include_directories(DepthFunction
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})