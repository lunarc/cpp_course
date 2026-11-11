#include <stats/descriptive.h>

#include <print>
#include <vector>

int main()
{
    // Measured yield stress [MPa] from a series of tensile tests.
    std::vector<double> yield = {251.3, 248.9, 255.1, 249.7, 252.4, 247.2, 253.8, 250.6};

    std::println("Mean   : {:.2f} MPa", stats::mean(yield));
    std::println("Median : {:.2f} MPa", stats::median(yield));
    std::println("Std dev: {:.2f} MPa", stats::stddev(yield));

    return 0;
}
