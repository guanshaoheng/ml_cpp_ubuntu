cmake_minimum_required(VERSION 3.0.0)
project(ml_cpp VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CUDA_COMPILER /usr/local/cuda-11.7/bin/nvcc)
find_package(Torch REQUIRED PATHS /home/shguan/libtorch)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

file(GLOB CPP_LIST "./*.cpp")

foreach(FILE_PATH IN LISTS CPP_LIST)
    STRING(REGEX REPLACE ".+/(.+)\\..*"  "\\1" FILE_NAME ${FILE_PATH}) 
    message(STATUS "==== ${FILE_NAME}: ${FILE_PATH}")
    add_executable(${FILE_NAME} ${FILE_PATH})
    target_link_libraries(${FILE_NAME} "${TORCH_LIBRARIES}")
    set_property(TARGET ${FILE_NAME} PROPERTY CXX_STANDARD 17)
endforeach()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
