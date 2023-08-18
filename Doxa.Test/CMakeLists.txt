message(STATUS "Doxa Test - CMake Build")

cmake_minimum_required(VERSION 3.16)
project(doxa_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    # so far so good
else()
    add_compile_options("-Wno-narrowing")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
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
  PerformanceTests.cpp
  PNMTests.cpp
  RegionTests.cpp
)

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