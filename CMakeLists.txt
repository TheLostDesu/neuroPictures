cmake_minimum_required(VERSION 3.24)
project(neuroPictures)

set(CMAKE_CXX_STANDARD 17)

include_directories(./include)
include_directories(./include/cuda/lib)
include_directories(./include/cuda/include)
include_directories(./lib)


add_library(utility STATIC nn/utility.cpp)
add_library(prc STATIC nn/perceptron.cpp)
add_library(nn STATIC nn/network.cpp)

add_executable(learner UI/learner.cpp)
target_link_libraries(learner)