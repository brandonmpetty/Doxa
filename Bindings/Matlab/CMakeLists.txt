cmake_minimum_required(VERSION 3.16)
project(DoxaMatlab)

set(CMAKE_GENERATOR_PLATFORM x64)

# Find MATLAB and its components
find_package(Matlab REQUIRED COMPONENTS MAIN_PROGRAM)

# Include the root Doxa directory for header files
include_directories(${CMAKE_SOURCE_DIR}/../../)

# Add each MEX file as a separate target
matlab_add_mex(NAME binarize SRC binarize.cpp)
matlab_add_mex(NAME update_in_place SRC update_in_place.cpp)
matlab_add_mex(NAME calculate_performance SRC calculate_performance.cpp)

# Set C++ standard for all targets
set_property(TARGET binarize update_in_place calculate_performance PROPERTY CXX_STANDARD 17)

# Define output directory for MEX files
set(MEX_OUTPUT_DIR ${CMAKE_BINARY_DIR}/mex)
file(MAKE_DIRECTORY ${MEX_OUTPUT_DIR})

set_property(TARGET binarize update_in_place calculate_performance PROPERTY RUNTIME_OUTPUT_DIRECTORY ${MEX_OUTPUT_DIR})

# Copy the class wrapper and test files to the build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Doxa.m DESTINATION ${MEX_OUTPUT_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test/test_doxa.m DESTINATION ${MEX_OUTPUT_DIR})

# Enable testing and add the MATLAB tests to CTest
enable_testing()
matlab_add_unit_test(
    NAME MatlabTests
    UNITTEST_FILE ${MEX_OUTPUT_DIR}/test_doxa.m
    ADDITIONAL_PATH ${MEX_OUTPUT_DIR}/$<CONFIG>
)