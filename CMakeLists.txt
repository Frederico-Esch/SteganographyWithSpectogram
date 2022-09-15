cmake_minimum_required(VERSION 3.22)
project(Steganography)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_CURRENT_LIST_DIR}/paths/LibPaths.cmake)

set(OpenCV_DIR PATH_TO_OPENCV)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Steganography
        main.cpp
        )

target_link_libraries(Steganography ${OpenCV_LIBS})