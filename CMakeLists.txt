cmake_minimum_required(VERSION 3.4)
project(magnumbase CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)