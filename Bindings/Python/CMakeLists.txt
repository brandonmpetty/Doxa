cmake_minimum_required(VERSION 2.8.12)

if (CMAKE_GENERATOR MATCHES "Visual Studio")
    set(CMAKE_GENERATOR_PLATFORM "x64" CACHE STRING "" FORCE)
endif()

project(doxapy)

find_package(PythonInterp REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_subdirectory(pybind11)
if (WIN32)
    add_compile_options("/std:c++17" "/permissive-")
else ()
    add_compile_options("-std=c++17")
endif ()
pybind11_add_module(doxapy DoxaPy.cpp)