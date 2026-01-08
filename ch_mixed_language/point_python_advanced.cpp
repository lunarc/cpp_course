#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include "point_advanced.h"

namespace py = pybind11;

PYBIND11_MODULE(point_advanced, m) {
    m.doc() = "Advanced Python bindings for Point and PointCloud classes";

    py::class_<Point>(m, "Point")
        .def(py::init<double, double>(), 
             py::arg("x") = 0.0, 
             py::arg("y") = 0.0,
             "Construct a Point with x and y coordinates")
        .def("distance_to", &Point::distance_to,
             py::arg("other"),
             "Calculate Euclidean distance to another point")
        .def_property("x", &Point::x, &Point::set_x, "X coordinate")
        .def_property("y", &Point::y, &Point::set_y, "Y coordinate")
        .def("__repr__", &Point::to_string)
        .def("__str__", &Point::to_string);

    py::class_<PointCloud>(m, "PointCloud")
        .def(py::init<>(), "Construct an empty PointCloud")
        .def("add_point", py::overload_cast<const Point&>(&PointCloud::add_point),
             py::arg("point"),
             "Add a Point to the cloud")
        .def("add_point", py::overload_cast<double, double>(&PointCloud::add_point),
             py::arg("x"),
             py::arg("y"),
             "Add a point with x and y coordinates")
        .def("__len__", &PointCloud::size, "Number of points in the cloud")
        .def("__getitem__", &PointCloud::get_point,
             py::arg("index"),
             "Get point at index",
             py::return_value_policy::reference_internal)
        .def("total_distance", &PointCloud::total_distance,
             "Calculate total path distance connecting all points")
        .def("centroid", &PointCloud::centroid,
             "Calculate the centroid of all points")
        .def_property_readonly("points", &PointCloud::get_points,
             "Get all points as a list");
}
