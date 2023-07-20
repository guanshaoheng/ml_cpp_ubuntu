cmake_minimum_required(VERSION 3.0.0)
project(ml_cpp VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(ml_cpp main.cpp)

add_subdirectory(./learn_torch)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
