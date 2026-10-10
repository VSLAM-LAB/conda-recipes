cmake_minimum_required(VERSION 3.16)
project(brisk_test CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(brisk REQUIRED)

add_executable(brisk_test main.cpp)
target_include_directories(brisk_test PRIVATE ${brisk_INCLUDE_DIRS})
target_link_libraries(brisk_test ${brisk_LIBRARIES} ${OpenCV_LIBRARIES})
