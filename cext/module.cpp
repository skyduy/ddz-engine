#include<pybind11/pybind11.h>
#include<pybind11/stl.h>
#include "move.h"

PYBIND11_MODULE(cext, m)
{
	m.def("get_actions", &getActions);
}