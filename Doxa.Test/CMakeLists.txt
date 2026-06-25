message(STATUS "Doxa Test - CMake Build")

cmake_minimum_required(VERSION 3.16)
project(doxa_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SIMD Options
option(DOXA_ENABLE_SIMD "Enable SIMD optimizations (compile all paths, runtime detection)" ON)

if(MSVC)
    # so far so good
else()
    add_compile_options("-Wno-narrowing")
endif()

# --------------------------------------------------------------------------
# TEST-ONLY: Disable FMA contraction in the test binary so that float-heavy
# algorithms (Feng in particular) produce byte-identical output across
# compilers.  Without this, Clang on Apple Silicon -- and any compiler with
# fast-math flags -- can fuse `a*b + c` into a single FMA instruction with
# one rounding step instead of two, producing 1-ULP differences that flip
# threshold-boundary pixels and break our byte-equal ground-truth pbm
# assertions.
#
# MSVC's default is /fp:precise which already prohibits fusion, so this is
# only needed for GCC and Clang.
#
# DO NOT USE THIS FLAG IN PRODUCTION BUILDS.  It is a CI determinism aid,
# not an algorithm correctness setting.  FMA is both faster AND more
# accurate (one rounding step instead of two) -- production users of Doxa
# should leave FMA enabled.  Disabling it here costs ~1-2% perf in the
# test binary and gives up ~1 ULP of accuracy in exchange for byte-equal
# output across Linux / macOS / Windows.  The Doxa core library is
# header-only, so this flag only affects this test executable; downstream
# projects that include Doxa headers are unaffected.
# --------------------------------------------------------------------------
if(NOT MSVC)
    add_compile_options("-ffp-contract=off")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(../Doxa)

add_executable(
  doxa_test
  AlgorithmTests.cpp
  BatainehTests.cpp
  BinarizationTests.cpp
  CalculatorTests.cpp
  ContrastImageTests.cpp
  GrayscaleTests.cpp
  ImageTests.cpp
  ISauvolaTests.cpp
  LocalWindowTests.cpp
  MorphologyTests.cpp
  PaletteTests.cpp
  ParametersTests.cpp
  ClassifiedPerformanceTests.cpp
  DRDMTests.cpp
  PNMTests.cpp
  DIBCOUtilsTests.cpp
  RegionTests.cpp
  SIMDTests.cpp
  SuTests.cpp
  WellnerTests.cpp
  FilterTests.cpp
  ConvolutionTests.cpp
  EdgeDetectorTests.cpp
  ThinningTests.cpp
  PseudoWeightsTests.cpp
)

# Platform detection and SIMD compiler flags
if(DOXA_ENABLE_SIMD)
    message(STATUS "SIMD optimizations: ENABLED (runtime detection)")

    # Detect platform and add appropriate flags
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64|x64")
        # x86-64: SSE2 is always available (baseline for x64)
        if(MSVC)
            # MSVC x64: SSE2 is enabled by default, no special flags needed
            message(STATUS "SIMD: x86-64 with SSE2 (MSVC)")
        else()
            # GCC/Clang: SSE2 is default for x64, but be explicit
            target_compile_options(doxa_test PRIVATE -msse2)
            message(STATUS "SIMD: x86-64 with SSE2 (GCC/Clang)")
        endif()

    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|ARM64")
        # ARM64: NEON is always available, no special flags needed on GCC/Clang
        # MSVC ARM64: NEON is enabled by default
        message(STATUS "SIMD: ARM64 with NEON")

    elseif(EMSCRIPTEN)
        # WASM: Add SIMD128 flag
        target_compile_options(doxa_test PRIVATE -msimd128)
        message(STATUS "SIMD: WebAssembly with SIMD128")

    else()
        message(STATUS "SIMD: Unknown platform, will use scalar fallback")
    endif()

else()
    message(STATUS "SIMD optimizations: DISABLED (scalar only)")
endif()

target_precompile_headers(
  doxa_test
  PUBLIC
    pch.h
)

target_link_libraries(
  doxa_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(
  doxa_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "System processor: ${CMAKE_SYSTEM_PROCESSOR}")