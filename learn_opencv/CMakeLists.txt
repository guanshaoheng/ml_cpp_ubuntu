cmake_minimum_required(VERSION 3.0.0)
project(ml_cpp VERSION 0.1.0 LANGUAGES C CXX)


file(GLOB CPP_LIST "./*.cpp")

foreach(FILE_PATH IN LISTS CPP_LIST)
    STRING(REGEX REPLACE ".+/(.+)\\..*"  "\\1" FILE_NAME ${FILE_PATH})
    message(STATUS "==== ${FILE_NAME}: ${FILE_PATH}")
    add_executable(${FILE_NAME} ${FILE_PATH} )
    target_link_libraries(${FILE_NAME} "${OpenCV_LIBS}")
    target_link_libraries(${FILE_NAME} "${TORCH_LIBRARIES}")
    set_property(TARGET ${FILE_NAME} PROPERTY CXX_STANDARD 17)
endforeach()


