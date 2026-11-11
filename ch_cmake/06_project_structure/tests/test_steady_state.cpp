// After a long time the temperature profile must become linear between
// the two boundary values.

#include <heat/heat1d.h>

#include <cmath>
#include <cstdio>
#include <print>

int main()
{
    const int n = 11;
    heat::Heat1D rod(n, 1.0, 1.0);
    rod.set_initial(std::vector<double>(n, 0.0));
    rod.set_boundary(100.0, 0.0);

    rod.advance(5.0, 0.9 * rod.max_stable_dt());

    for (int i = 0; i < n; ++i)
    {
        const double expected = 100.0 * (1.0 - i * rod.dx());
        const double error = std::abs(rod.temperature()[i] - expected);
        if (error > 1e-6)
        {
            std::println(stderr, "Point {}: got {}, expected {}", i, rod.temperature()[i], expected);
            return 1;
        }
    }

    std::println("Steady state OK");
    return 0;
}
