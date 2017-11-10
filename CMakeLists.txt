cmake_minimum_required(VERSION 3.5)

# Project
set(PROJECT_NAME c-final-exam)
set(PROJECT_VERSION "1.0.0")
set(PROJECT_DESC "Final exam project for C Programming Language")
set(PROJECT_URL "https://github.com/HDU421/c-final-exam")
set(PROJECT_ISSUES_URL "https://github.com/HDU421/c-final-exam/issues")
project(${PROJECT_NAME})

# Compiler
set(CMAKE_CXX_COMPILER "gcc")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXX_FLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXX_FLAGS} -O3 -Wall")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

# Subdirectories
add_subdirectory(lib)
add_subdirectory(src)
