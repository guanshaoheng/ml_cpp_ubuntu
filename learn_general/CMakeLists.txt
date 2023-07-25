cmake_minimum_required(VERSION 3.0.0)

# 将头文件中的函数作为链接库编译
include_directories(./include)
file(GLOB LIB_CPP "./include/*.cpp")
add_library(LIBSELF SHARED ${LIB_CPP})

file(GLOB CPP_LIST "./*.cpp")

FOREACH (FILE_PATH IN LISTS CPP_LIST)
    STRING(REGEX REPLACE ".+/(.+)\\..*"  "\\1" FILE_NAME ${FILE_PATH})
    message(STATUS "==== ${FILE_NAME}: ${FILE_PATH}")
    add_executable(${FILE_NAME} ${FILE_PATH} )
    target_link_libraries(${FILE_NAME} LIBSELF)  # 链接自己写的库函数  # 注意 链接链接库的时候不要添加${}
    set_property(TARGET ${FILE_NAME} PROPERTY CXX_STANDARD 17)
ENDFOREACH ()