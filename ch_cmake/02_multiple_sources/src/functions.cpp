#include "functions.h"

#include <cmath>

double x_exp_x(double x)
{
    return x * std::exp(x);
}

double damped_oscillation(double x)
{
    return std::exp(-0.1 * x) * std::sin(x);
}
