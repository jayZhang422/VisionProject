cmake_minimum_required(VERSION 3.10)

project(Vision_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 

find_package(OpenCV REQUIRED)

file(GLOB_RECURSE ALL_SOURCES "src/*.cpp")
 

add_executable(vision_app ${ALL_SOURCES})


target_link_libraries(vision_app ${OpenCV_LIBS})


message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")