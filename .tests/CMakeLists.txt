# CMake build for the GoogleTest unit tests.
# 
# @copyright Copyright (c) 2026 YH Choi. All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
# 
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE

cmake_minimum_required(VERSION 3.16)

project(ino_interpreter_tests LANGUAGES CXX)

# --- GoogleTest ---------------------------------------------------------------

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.tar.gz
    URL_HASH SHA256=65fab701d9829d38cb77c14acdc431d2108bfdbf8979e40eb8ae567edf10b27c
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# --- Library under test -------------------------------------------------------

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)

# The library itself targets Arduino, so it is built as C++11 to keep it honest.
file(GLOB_RECURSE LIBRARY_SOURCES CONFIGURE_DEPENDS ${SRC_DIR}/structs/*.cpp)
list(FILTER LIBRARY_SOURCES EXCLUDE REGEX "/cpp_data_structures_and_algorithms/")

add_library(ino_interpreter_structs STATIC ${LIBRARY_SOURCES})
set_target_properties(ino_interpreter_structs PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_compile_options(ino_interpreter_structs PRIVATE -Wall)

# --- Test support -------------------------------------------------------------

# An object library, so the replacement new/delete operators
# are always linked into every test binary.
add_library(mem_leak OBJECT mem_leak.cpp)
target_link_libraries(mem_leak PUBLIC GTest::gtest)
set_target_properties(mem_leak PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# --- Tests --------------------------------------------------------------------

# GoogleTest 1.17 needs C++17, so the test sources are built as C++17.
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/structs/test*.cpp)

enable_testing()

foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    set_target_properties(${test_name} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )
    target_compile_options(${test_name} PRIVATE -Wall)
    target_link_libraries(${test_name} PRIVATE
        mem_leak
        ino_interpreter_structs
        GTest::gtest_main
    )
    gtest_discover_tests(${test_name})
endforeach()
