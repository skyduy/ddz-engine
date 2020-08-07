add_library(COMMON INTERFACE)
target_include_directories(COMMON INTERFACE ${PROJECT_SOURCE_DIR}/src)

add_library(ddz::common ALIAS COMMON)
