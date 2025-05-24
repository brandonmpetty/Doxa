message(STATUS "DoxaPy - CMake Build")

cmake_minimum_required(VERSION 3.16...3.27)
project(doxapy)

if (CMAKE_VERSION VERSION_LESS 3.18)
  set(DEV_MODULE Development)
else()
  set(DEV_MODULE Development.Module)
endif()

find_package(Python 3.12 
  REQUIRED COMPONENTS Interpreter ${DEV_MODULE} 
  OPTIONAL_COMPONENTS Development.SABIModule
)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(NB_TARGET_ABI_VERSION=312)

if(MSVC)
    # so far so good
else()
    add_compile_options("-Wno-narrowing")
endif()

# Detect the installed nanobind package and import it into CMake
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT
)
find_package(nanobind CONFIG REQUIRED)

include_directories(./src/Doxa)

nanobind_add_module(
  doxapy                   # Target name
  NB_STATIC STABLE_ABI LTO # Optional flags (see below)
  src/DoxaPy.cpp
)

install(TARGETS doxapy LIBRARY DESTINATION doxapy)
