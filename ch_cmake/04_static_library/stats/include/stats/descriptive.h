#pragma once

#include <span>

namespace stats {

double mean(std::span<const double> x);
double variance(std::span<const double> x); // sample variance (n - 1)
double stddev(std::span<const double> x);
double median(std::span<const double> x);

} // namespace stats
