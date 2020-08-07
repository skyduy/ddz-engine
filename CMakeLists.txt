cmake_minimum_required(VERSION 3.5)
project(ddz)

add_subdirectory(src/common)
add_subdirectory(src/rule)

add_subdirectory(samples)

enable_testing()
add_subdirectory(tests)
