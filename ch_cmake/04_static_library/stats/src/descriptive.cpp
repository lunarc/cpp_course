#include <stats/descriptive.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

namespace stats {

double mean(std::span<const double> x)
{
    return std::accumulate(x.begin(), x.end(), 0.0) / static_cast<double>(x.size());
}

double variance(std::span<const double> x)
{
    const double m = mean(x);
    double sum = 0.0;
    for (double v : x)
        sum += (v - m) * (v - m);
    return sum / static_cast<double>(x.size() - 1);
}

double stddev(std::span<const double> x)
{
    return std::sqrt(variance(x));
}

double median(std::span<const double> x)
{
    std::vector<double> sorted(x.begin(), x.end());
    std::sort(sorted.begin(), sorted.end());

    const auto n = sorted.size();
    return n % 2 == 1 ? sorted[n / 2] : 0.5 * (sorted[n / 2 - 1] + sorted[n / 2]);
}

} // namespace stats
