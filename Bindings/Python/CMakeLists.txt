cmake_minimum_required(VERSION 2.8.12)
project(doxapy)

find_package(PythonInterp REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_subdirectory(pybind11)
add_compile_options("/std:c++17" "/permissive-")
pybind11_add_module(doxapy DoxaPy.cpp)
