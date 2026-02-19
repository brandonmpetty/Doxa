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
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
endif()

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(NB_TARGET_ABI_VERSION=312)

# SIMD support for Python bindings
option(DOXAPY_ENABLE_SIMD "Enable SIMD in Python bindings" ON)

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
  doxapy
  NB_STATIC STABLE_ABI LTO NOMINSIZE
  src/DoxaPy.cpp
)

# Speed optimization for header-only library (algorithms compile within binding module)
target_compile_options(doxapy PRIVATE
    $<$<AND:$<NOT:$<CONFIG:Debug>>,$<CXX_COMPILER_ID:MSVC>>:/O2>
    $<$<AND:$<NOT:$<CONFIG:Debug>>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-O3>
)

# Platform-specific SIMD flags (same logic as test)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64|x64")
    # x86-64: SSE2 is always available (baseline for x64)
    if(MSVC)
        # MSVC x64: SSE2 is enabled by default, no special flags needed
        message(STATUS "DoxaPy SIMD: x86-64 with SSE2 (MSVC)")
    else()
        # GCC/Clang: SSE2 is default for x64, but be explicit
        target_compile_options(doxapy PRIVATE -msse2)
        message(STATUS "DoxaPy SIMD: x86-64 with SSE2 (GCC/Clang)")
    endif()

elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|ARM64")
    message(STATUS "DoxaPy SIMD: ARM64 with NEON")

endif()

# Copy built module to dist/ directory (mirrors WASM pattern)
add_custom_command(TARGET doxapy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/dist
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:doxapy>
        ${CMAKE_CURRENT_SOURCE_DIR}/dist/
    COMMENT "Copying doxapy module to dist/"
)

install(TARGETS doxapy LIBRARY DESTINATION doxapy)
