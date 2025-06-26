cmake_minimum_required(VERSION 3.21)
project(solver-test LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-as-needed -ldl")

set(COMMON_SOURCES main.cpp)

add_executable(test-cbc ${COMMON_SOURCES})
target_compile_definitions(test-cbc PRIVATE -DSOLVER_CLASS=CbcWrapper)
target_include_directories(test-cbc PRIVATE "/usr/local/include/cbc")
target_link_directories(test-cbc PRIVATE "/usr/lib/x86_64-linux-gnu")
target_link_libraries(test-cbc PRIVATE Osi OsiCbc OsiClp Cbc Clp CbcSolver)

add_executable(test-highs ${COMMON_SOURCES})
target_compile_definitions(test-highs PRIVATE -DSOLVER_CLASS=HighsWrapper)
target_include_directories(test-highs PRIVATE "/usr/local/include/highs")
target_link_libraries(test-highs PRIVATE highs)

add_executable(test-scip ${COMMON_SOURCES})
target_compile_definitions(test-scip PRIVATE -DSOLVER_CLASS=ScipWrapper)
target_include_directories(test-scip PRIVATE "/usr/include/scip")
target_link_directories(test-scip PRIVATE "/usr/lib/scip")
target_link_libraries(test-scip PRIVATE scip)

add_executable(test-copt ${COMMON_SOURCES})
target_compile_definitions(test-copt PRIVATE -DSOLVER_CLASS=CoptWrapper)
target_include_directories(test-copt PRIVATE
    "/usr/include/copt"
    "/usr/include/copt/coptcpp_inc")
target_link_directories(test-copt PRIVATE "/usr/lib/copt")
target_link_libraries(test-copt PRIVATE copt_cpp)
