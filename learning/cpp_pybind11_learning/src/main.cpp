#include "Option_pricing.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;



// pybind11封装c++类
PYBIND11_MODULE(Option_pricing, m)
{
    py::class_<Option_pricing>(m, "Option_pricing")
        .def(py::init<>()) // 初始化构造函数
        .def("standard_brownian", &Option_pricing::standard_brownian)
        .def("general_brownian", &Option_pricing::general_brownian)
        .def("geo_brownian", &Option_pricing::geo_brownian)
        .def("BSM", &Option_pricing::BSM)
        .def("BSM_binary", &Option_pricing::BSM_binary)
        .def("BSM_newton", &Option_pricing::BSM_newton)
        .def("Euro_greeks1", &Option_pricing::Euro_greeks1)
        .def("Euro_greeks2", &Option_pricing::Euro_greeks2)
        .def("Ame_CCR", &Option_pricing::Ame_CCR)
        .def("find_Sx", &Option_pricing::find_Sx)
        .def("BAW", &Option_pricing::BAW)
        .def("BAW_binary", &Option_pricing::BAW_binary);
}