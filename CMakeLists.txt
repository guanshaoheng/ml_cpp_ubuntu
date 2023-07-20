cmake_minimum_required(VERSION 3.0.0)
project(ml_cpp VERSION 0.1.0 LANGUAGES C CXX)

# ====================================
# opencv
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# ====================================
# Torch
set(CMAKE_CUDA_COMPILER /usr/local/cuda-11.7/bin/nvcc)
find_package(Torch REQUIRED PATHS /home/shguan/libtorch_abi)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")


include_directories(./utils)
add_executable(ml_cpp main.cpp)

# ===============================
# 包含子目录中的cmakelists.txt文件
add_subdirectory(./learn_torch)
add_subdirectory(./learn_opencv)
add_subdirectory(./learn_torch_opencv)

