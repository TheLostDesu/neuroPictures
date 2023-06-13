cmake_minimum_required(VERSION 3.24)
project(neuroPictures)

set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR "${VCPKG_INSTALLED_DIR}/include/vcpkg/installed/x86-windows/share/opencv2")
find_package(OpenCV REQUIRED)


add_executable(
        editor.cpp
        interface.cpp
        interface.h)
