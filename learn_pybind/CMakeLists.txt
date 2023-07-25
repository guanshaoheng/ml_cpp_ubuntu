cmake_minimum_required( VERSION 3.0.0)

include_directories(include)
add_library(mymath SHARED ./include/utils.cpp )

add_subdirectory(./pybind11)
pybind11_add_module(example pybind_example.cpp)
target_link_libraries(example PRIVATE mymath)

