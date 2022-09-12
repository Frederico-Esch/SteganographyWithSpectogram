cmake_minimum_required(VERSION 3.22)
project(Steganography)

set(CMAKE_CXX_STANDARD 20)

set(OpenCV_DIR "E:\\Progs\\opencv\\build\\x64\\vc15\\lib")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Steganography
        main.cpp
        )

target_link_libraries(Steganography ${OpenCV_LIBS})