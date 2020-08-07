add_library(RULE STATIC rule.cpp)
target_include_directories(RULE PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library(ddz::rule ALIAS RULE)
