cmake_minimum_required(VERSION 3.16)
project(DoxaMatlab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find MATLAB and its components
find_package(Matlab REQUIRED COMPONENTS MAIN_PROGRAM)

# Include the root Doxa directory for header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../..)

# Define output directory for MEX files and Matlab sources
set(MEX_OUTPUT_DIR ${CMAKE_BINARY_DIR}/mex)
file(MAKE_DIRECTORY ${MEX_OUTPUT_DIR})

# Add each MEX file as a separate target
matlab_add_mex(NAME image_mex SRC ImageMex.cpp)
matlab_add_mex(NAME binarize_mex SRC BinarizeMex.cpp)
matlab_add_mex(NAME update_to_binary_mex SRC UpdateToBinaryMex.cpp)
matlab_add_mex(NAME calculate_performance_mex SRC CalculatePerformanceMex.cpp)

# All MEX targets
set(MEX_TARGETS image_mex binarize_mex update_to_binary_mex calculate_performance_mex)

# Set output directory for all MEX targets
set_property(TARGET ${MEX_TARGETS} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${MEX_OUTPUT_DIR})

# SIMD optimizations
option(DOXA_ENABLE_SIMD "Enable SIMD optimizations" ON)
if(DOXA_ENABLE_SIMD)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64|x64")
        if(NOT MSVC)
            foreach(target ${MEX_TARGETS})
                target_compile_options(${target} PRIVATE -msse2)
            endforeach()
        endif()
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|ARM64")
        # ARM64: NEON is enabled by default
    endif()
endif()

# Copy test files to the build directory (for CTest)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test/TestDoxa.m DESTINATION ${MEX_OUTPUT_DIR})

# Copy +Doxa package alongside the MEX files.
# TARGET_FILE_DIR resolves to the correct output directory on both
# single-config (mex/) and multi-config (mex/Release/) generators.
add_custom_command(TARGET image_mex POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/+Doxa
        $<TARGET_FILE_DIR:image_mex>/+Doxa
)

# Enable testing and add the MATLAB tests to CTest
enable_testing()
matlab_add_unit_test(
    NAME MatlabTests
    UNITTEST_FILE ${MEX_OUTPUT_DIR}/TestDoxa.m
    ADDITIONAL_PATH ${MEX_OUTPUT_DIR}/$<CONFIG>
)
