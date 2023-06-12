cmake_minimum_required(VERSION 3.24)
project(neuroPictures)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "/include/opencv2")

find_package(OpenCV CONFIG REQUIRED)


add_executable(
        editor.cpp
        interface.cpp
        interface.h)
