cmake_minimum_required(VERSION 3.16)
project(doxajs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This file is only used when building with Emscripten
if(NOT EMSCRIPTEN)
    message(FATAL_ERROR "This CMakeLists.txt requires Emscripten. Use: emcmake cmake ..")
endif()

option(DOXAJS_ENABLE_SIMD "Enable WASM SIMD128" ON)

# Include Doxa headers
include_directories(${CMAKE_SOURCE_DIR}/Doxa)

# Create WASM module
add_executable(doxaWasm DoxaWasm.cpp)

# Emscripten compile/link flags (matches build.js)
target_compile_options(doxaWasm PRIVATE
    $<IF:$<CONFIG:Debug>,-O0,-O3>
    $<$<CONFIG:Debug>:-g>
)

target_link_options(doxaWasm PRIVATE
    -sWASM=1
    -sNO_EXIT_RUNTIME=1
    -sALLOW_MEMORY_GROWTH=1
    "-sEXPORTED_FUNCTIONS=['_malloc','_free']"
    "-sEXPORTED_RUNTIME_METHODS=['HEAPU8']"
    --bind
    # Debug-only options
    $<$<CONFIG:Debug>:-sEXCEPTION_DEBUG>
    $<$<CONFIG:Debug>:-sNO_DISABLE_EXCEPTION_CATCHING>
    $<$<CONFIG:Debug>:-g4>
    "$<$<CONFIG:Debug>:--source-map-base=http://localhost:8080/>"
)

# SIMD support
if(DOXAJS_ENABLE_SIMD)
    target_compile_options(doxaWasm PRIVATE -msimd128)
    message(STATUS "DoxaJs SIMD: ENABLED (SIMD128)")
else()
    message(STATUS "DoxaJs SIMD: DISABLED")
endif()

# Output to dist/ directory
set_target_properties(doxaWasm PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist
)

# Copy JavaScript wrapper after build
add_custom_command(TARGET doxaWasm POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/doxa.js
        ${CMAKE_CURRENT_SOURCE_DIR}/dist/doxa.js
    COMMENT "Copying doxa.js wrapper to dist/"
)

# CTest integration - run Jasmine tests via Node
include(CTest)
enable_testing()

# Platform-specific script extension (avoid picking up .cmd on WSL2)
if(WIN32)
    set(CMD_EXT ".cmd")
else()
    set(CMD_EXT "")
endif()

find_program(NPM_EXECUTABLE NAMES npm${CMD_EXT})

if(NPM_EXECUTABLE)
    add_test(NAME wasm_tests
        COMMAND ${NPM_EXECUTABLE} test
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()
