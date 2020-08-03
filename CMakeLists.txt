# CMake
cmake_minimum_required(VERSION 3.10)

# Project
project(ddz VERSION 1.0)

# ------------
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
