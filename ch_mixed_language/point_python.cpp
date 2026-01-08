#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "point.h"

namespace py = pybind11;

PYBIND11_MODULE(point_module, m) {
    m.doc() = "Python bindings for Point class using pybind11";

    py::class_<Point>(m, "Point")
        .def(py::init<double, double>(), 
             py::arg("x"), 
             py::arg("y"),
             "Construct a Point with x and y coordinates")
        .def("distance_to", &Point::distance_to,
             py::arg("other"),
             "Calculate distance to another point");
}
