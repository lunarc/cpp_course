#include <pybind11/pybind11.h>

int add(int a, int b) {
    return a + b;
}

PYBIND11_MODULE(test_ext, m) {
    m.def("add", &add, "Add two numbers");
}