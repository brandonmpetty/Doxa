cmake_minimum_required(VERSION 3.16)
project(doxa VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build options
option(DOXA_BUILD_CPP_TESTS "Build C++ unit tests" ON)
option(DOXA_BUILD_PYTHON "Build Python bindings" OFF)
option(DOXA_BUILD_WASM "Build WebAssembly bindings (requires emcmake)" OFF)
option(DOXA_BUILD_BENCHMARKS "Build performance benchmarks (Google Benchmark)" OFF)
option(DOXA_BUILD_MATLAB "Build MATLAB MEX bindings (requires MATLAB)" OFF)
option(DOXA_ENABLE_SIMD "Enable SIMD optimizations" ON)

# Enable CTest for all test types
include(CTest)
enable_testing()

# Propagate SIMD option to subdirectories
set(DOXA_ENABLE_SIMD ${DOXA_ENABLE_SIMD} CACHE BOOL "" FORCE)
set(DOXAPY_ENABLE_SIMD ${DOXA_ENABLE_SIMD} CACHE BOOL "" FORCE)

# C++ Tests (native build only)
if(DOXA_BUILD_CPP_TESTS AND NOT EMSCRIPTEN)
    add_subdirectory(Doxa.Test)
endif()

# Performance Benchmarks (native build only, always Release)
if(DOXA_BUILD_BENCHMARKS AND NOT EMSCRIPTEN)
    add_subdirectory(Doxa.Bench)
endif()

# Python Bindings (native build only)
if(DOXA_BUILD_PYTHON AND NOT EMSCRIPTEN)
    find_package(Python 3.12 REQUIRED COMPONENTS Interpreter)
    # Sync headers from core library
    execute_process(
        COMMAND ${Python_EXECUTABLE} copy-cpp-files.py
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Bindings/Python
    )
    add_subdirectory(Bindings/Python)

    # Add Python tests to CTest
    add_test(NAME python_tests
        COMMAND ${Python_EXECUTABLE} -m unittest discover -s test -p "test_*.py" -v
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Bindings/Python
    )
    # Set PYTHONPATH so tests can find the built doxapy module in dist/
    set_tests_properties(python_tests PROPERTIES
        ENVIRONMENT "PYTHONPATH=${CMAKE_SOURCE_DIR}/Bindings/Python/dist"
    )
endif()

# MATLAB MEX Bindings (native build only)
if(DOXA_BUILD_MATLAB AND NOT EMSCRIPTEN)
    add_subdirectory(Bindings/Matlab)
endif()

# WebAssembly - two modes:
# 1. Direct Emscripten build (when using emcmake)
# 2. ExternalProject build (when doing native build with DOXA_BUILD_WASM=ON)
if(EMSCRIPTEN)
    add_subdirectory(Bindings/WebAssembly)
elseif(DOXA_BUILD_WASM)
    # Platform-specific script extensions (avoid picking up .cmd/.bat on WSL2)
    if(WIN32)
        set(CMD_EXT ".cmd")
        set(BAT_EXT ".bat")
    else()
        set(CMD_EXT "")
        set(BAT_EXT "")
    endif()

    # Build WASM as external project using emcmake
    find_program(EMCMAKE NAMES emcmake${BAT_EXT}
        HINTS ENV EMSDK
        PATH_SUFFIXES upstream/emscripten
    )

    if(EMCMAKE)
        message(STATUS "Found emcmake: ${EMCMAKE}")
        include(ExternalProject)
        ExternalProject_Add(wasm_build
            SOURCE_DIR ${CMAKE_SOURCE_DIR}
            BINARY_DIR ${CMAKE_BINARY_DIR}/wasm
            CONFIGURE_COMMAND ${EMCMAKE} cmake ${CMAKE_SOURCE_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            BUILD_COMMAND cmake --build . --config ${CMAKE_BUILD_TYPE}
            INSTALL_COMMAND ""
            TEST_COMMAND ""
        )
        # Add WASM tests to CTest (runs after wasm_build)
        find_program(NPM_EXECUTABLE NAMES npm${CMD_EXT})
        if(NPM_EXECUTABLE)
            add_test(NAME wasm_tests
                COMMAND ${NPM_EXECUTABLE} test
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Bindings/WebAssembly
            )
        endif()
    else()
        message(WARNING "DOXA_BUILD_WASM=ON but emcmake not found. "
            "Make sure Emscripten SDK is installed and run emsdk_env before configuring CMake.")
    endif()
endif()
