#pragma once

#include <functional>

// Numerical integration of f over [a, b] using n sub-intervals.
double trapezoidal(const std::function<double(double)>& f, double a, double b, int n);
double simpson(const std::function<double(double)>& f, double a, double b, int n);
