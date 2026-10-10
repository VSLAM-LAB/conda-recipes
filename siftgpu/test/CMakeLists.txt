cmake_minimum_required(VERSION 3.18)
project(siftgpu_test CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(SiftGPU CONFIG REQUIRED)

add_executable(siftgpu_test main.cpp)
target_link_libraries(siftgpu_test SiftGPU::sift_gpu)
