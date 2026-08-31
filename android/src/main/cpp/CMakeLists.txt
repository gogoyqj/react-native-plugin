cmake_minimum_required(VERSION 3.10)

project(circleplugin)

set(CMAKE_CXX_STANDARD 17)

# C++ 源文件
add_library(circleplugin SHARED
    CirclePluginJNI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../cpp/CircleDrawer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../cpp/CircleJSI.cpp
)

target_include_directories(circleplugin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../cpp
)

# React Native JSI 头文件路径
# 实际项目中需要根据 node_modules 路径调整
target_include_directories(circleplugin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../node_modules/react-native/ReactCommon/jsi
)

# Link Android log library
find_library(log-lib log)
target_link_libraries(circleplugin ${log-lib})
