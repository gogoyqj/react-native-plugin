cmake_minimum_required(VERSION 3.10)

project(circleplugin)

set(CMAKE_CXX_STANDARD 17)

# React Native JSI 路径
if(DEFINED REACT_NATIVE_DIR AND NOT REACT_NATIVE_DIR STREQUAL "")
    set(JSI_DIR ${REACT_NATIVE_DIR}/ReactCommon/jsi)
else()
    set(JSI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../node_modules/react-native/ReactCommon/jsi)
endif()

# C++ 源文件 + JSI 源码 (避免链接 libjsi.so)
add_library(circleplugin SHARED
    CirclePluginJNI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../cpp/CircleDrawer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../cpp/CirclePluginTurboModule.cpp
    ${JSI_DIR}/jsi/jsi.cpp
)

target_include_directories(circleplugin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../cpp
    ${JSI_DIR}
)

# Link Android log library
find_library(log-lib log)
target_link_libraries(circleplugin ${log-lib})
