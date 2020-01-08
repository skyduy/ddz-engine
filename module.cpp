#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include "core.h"

PYBIND11_MODULE(ddz, m)
{
	m.def("get_moves", &getActions);
}
