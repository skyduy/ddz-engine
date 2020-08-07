find_package(pybind11 CONFIG REQUIRED)
add_library(ddz SHARED ddz.cpp)
target_link_libraries(ddz PRIVATE ddz::rule pybind11::embed pybind11::module pybind11::pybind11)

install(TARGETS ddz)
