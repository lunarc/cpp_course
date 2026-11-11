#pragma once

#include <span>

namespace stats {

struct LinearFit
{
    double slope;
    double intercept;
    double r2; // coefficient of determination
};

// Least squares fit of y = slope * x + intercept.
LinearFit linear_fit(std::span<const double> x, std::span<const double> y);

} // namespace stats
