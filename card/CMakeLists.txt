project(card)

# library
add_library(${PROJECT_NAME} STATIC src/rule.cpp)
add_library(ddz::card ALIAS ${PROJECT_NAME})
target_include_directories( ${PROJECT_NAME} PUBLIC include)

# exec demo
add_executable(demo demo_main.cpp)
target_link_libraries(demo PRIVATE ddz::card)
