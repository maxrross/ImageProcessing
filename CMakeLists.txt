cmake_minimum_required(VERSION 3.21)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 14)

include_directories(cmake-build-debug/src)

add_executable(ImageProcessing
        cmake-build-debug/src/image.cpp
        cmake-build-debug/src/image.h
        cmake-build-debug/src/main.cpp
        cmake-build-debug/src/main.h)
