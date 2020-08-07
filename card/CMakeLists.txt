# library
add_library(card STATIC src/rule.cpp)
target_include_directories(card PUBLIC include)

add_library(ddz::card ALIAS card)

# exec demo
add_executable(demo demo_main.cpp)
target_link_libraries(demo PRIVATE ddz::card)
