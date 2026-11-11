#pragma once

#include <functional>

namespace quad {

using Function = std::function<double(double)>;

// Integrate f over [a, b] with n sub-intervals. Throws
// std::invalid_argument if n < 1.
double trapezoidal(const Function& f, double a, double b, int n);
double simpson(const Function& f, double a, double b, int n);

// Two-point Gauss-Legendre rule on each of n sub-intervals.
double gauss2(const Function& f, double a, double b, int n);

} // namespace quad
