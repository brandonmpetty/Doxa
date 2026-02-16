message(STATUS "Doxa Bench - CMake Build")

cmake_minimum_required(VERSION 3.16)
project(doxa_bench)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SIMD Options
option(DOXA_ENABLE_SIMD "Enable SIMD optimizations (compile all paths, runtime detection)" ON)

if(MSVC)
    # so far so good
else()
    add_compile_options("-Wno-narrowing")
endif()

include(FetchContent)
FetchContent_Declare(
  googlebenchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.9.1.zip
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

include_directories(../Doxa)

# Resolve absolute path to test resources (shared with Doxa.Test)
get_filename_component(DOXA_RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Doxa.Test/Resources" ABSOLUTE)
configure_file(config.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/config.hpp @ONLY)

add_executable(
  doxa_bench
  GlobalThresholdBenchmarks.cpp
  ClassifiedPerformanceBenchmarks.cpp
  DRDMBenchmarks.cpp
  CalculatorBenchmarks.cpp
  BinarizationBenchmarks.cpp
)

target_include_directories(doxa_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# Platform detection and SIMD compiler flags
if(DOXA_ENABLE_SIMD)
    message(STATUS "SIMD optimizations: ENABLED (runtime detection)")

    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64|x64")
        if(MSVC)
            message(STATUS "SIMD: x86-64 with SSE2 (MSVC)")
        else()
            target_compile_options(doxa_bench PRIVATE -msse2)
            message(STATUS "SIMD: x86-64 with SSE2 (GCC/Clang)")
        endif()

    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|ARM64")
        message(STATUS "SIMD: ARM64 with NEON")

    elseif(EMSCRIPTEN)
        target_compile_options(doxa_bench PRIVATE -msimd128)
        message(STATUS "SIMD: WebAssembly with SIMD128")

    else()
        message(STATUS "SIMD: Unknown platform, will use scalar fallback")
    endif()

else()
    message(STATUS "SIMD optimizations: DISABLED (scalar only)")
endif()

target_precompile_headers(
  doxa_bench
  PUBLIC
    pch.h
)

target_link_libraries(
  doxa_bench
  benchmark::benchmark
  benchmark::benchmark_main
)

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "System processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "Resources: ${DOXA_RESOURCES_DIR}")
