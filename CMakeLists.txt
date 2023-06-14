cmake_minimum_required(VERSION 3.24)
project(neuroPictures)

set(CMAKE_CXX_STANDARD 17)


include_directories(/include)
include_directories(/include/cuda/lib)
include_directories(/include/cuda/include)
include_directories(/lib)

add_library(utility STATIC nn/utility.cpp)
add_library(gpu1 STATIC GPU_stuff/matrix_mul.cpp)
add_library(gpu2 STATIC GPU_stuff/detect_device.cpp)


add_executable(test tests/tests.cpp)
target_link_libraries(test utility gpu1 gpu2)