cmake_minimum_required(VERSION 3.16)
project(UpdateToBinary)

find_package(Matlab REQUIRED)

include_directories(../../)

matlab_add_mex(
    NAME update_to_binary 
    SRC DoxaMat.cpp
)

set_target_properties(update_to_binary PROPERTIES CXX_STANDARD 17)

set_target_properties(update_to_binary PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/dist
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/dist
)

# Copy the class wrapper .m file to the dist folder
file(COPY ${CMAKE_SOURCE_DIR}/doxa.m DESTINATION ${CMAKE_SOURCE_DIR}/dist)
