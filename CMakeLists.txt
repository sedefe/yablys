cmake_minimum_required(VERSION 3.21)
project(solver-test LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-as-needed -ldl")

set(COMMON_SOURCES main.cpp)
include_directories(${CMAKE_SOURCE_DIR}/include)

option(USE_CBC OFF)
if(USE_CBC)
    add_definitions(-DUSE_CBC)
    add_executable(test-cbc ${COMMON_SOURCES})
    target_compile_definitions(test-cbc PRIVATE -DSOLVER_CLASS=CbcWrapper)
    target_link_libraries(test-cbc PRIVATE Osi OsiCbc OsiClp Cbc Clp CbcSolver)
endif()

option(USE_HIGHS OFF)
if(USE_HIGHS)
    find_package(HIGHS REQUIRED)
    add_executable(test-highs ${COMMON_SOURCES})
    target_compile_definitions(test-highs PRIVATE -DSOLVER_CLASS=HighsWrapper)
    target_include_directories(test-highs PRIVATE ${HIGHS_INCLUDE_DIRS}/highs)
    target_link_libraries(test-highs PRIVATE ${HIGHS_LIBRARIES})
endif()

option(USE_SCIP OFF)
if(USE_SCIP)
    find_package(SCIP REQUIRED)
    add_executable(test-scip ${COMMON_SOURCES})
    target_compile_definitions(test-scip PRIVATE -DSOLVER_CLASS=ScipWrapper)
    target_link_libraries(test-scip PRIVATE ${SCIP_LIBRARIES})
endif()

option(USE_COPT OFF)
if(USE_COPT)
    add_executable(test-copt ${COMMON_SOURCES})
    target_compile_definitions(test-copt PRIVATE -DSOLVER_CLASS=CoptWrapper)
    target_include_directories(test-copt PRIVATE
        "/usr/include/copt"
        "/usr/include/copt/coptcpp_inc")
    target_link_directories(test-copt PRIVATE "/usr/lib/copt")
    target_link_libraries(test-copt PRIVATE copt_cpp)
endif()
