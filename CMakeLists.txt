cmake_minimum_required(VERSION 3.22)
project(Steganography)

set(CMAKE_CXX_STANDARD 20)

add_executable(Steganography
        main.cpp
        Image.cpp
        Manipulator.cpp Manipulator.h)