#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // for automatic conversions

#include "rule/rule.h"

namespace py = pybind11;

PYBIND11_MODULE(ddz, m) {
    m.doc() = "斗地主插件";
    m.def("get_actions", &getActions, "斗地主出牌规则");
}
