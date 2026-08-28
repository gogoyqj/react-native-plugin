cmake_minimum_required(VERSION 3.10)

project(circleplugin)

set(CMAKE_CXX_STANDARD 17)

# C++ source files
add_library(circleplugin SHARED
    CirclePluginJNI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../cpp/CircleDrawer.cpp
)

target_include_directories(circleplugin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../cpp
)

# Link Android log library
find_library(log-lib log)
target_link_libraries(circleplugin ${log-lib})
