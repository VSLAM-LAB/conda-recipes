cmake_minimum_required(VERSION 3.16)
project(akaze_test CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(akaze REQUIRED)
if(NOT akaze_LIBRARY OR NOT akaze_INCLUDE_DIR)
  message(FATAL_ERROR "akazeConfig.cmake: library '${akaze_LIBRARY}', include dir '${akaze_INCLUDE_DIR}'")
endif()

add_executable(akaze_test main.cpp)
target_include_directories(akaze_test PRIVATE ${akaze_INCLUDE_DIRS})
target_link_libraries(akaze_test ${akaze_LIBRARIES} ${OpenCV_LIBRARIES})
