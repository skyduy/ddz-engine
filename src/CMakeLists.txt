# lib ddz
add_library(DDZ_CORE core.cpp)
add_library(UTILS utils.cpp)

# interface
target_include_directories(DDZ_CORE INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(UTILS INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# exec main
add_executable(main main.cpp)
target_link_libraries(main PRIVATE DDZ_CORE UTILS)
