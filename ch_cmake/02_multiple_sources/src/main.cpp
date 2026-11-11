#include "functions.h"
#include "integration.h"

#include <cmath>
#include <print>

int main()
{
    // The integral of x * exp(x) over [0, 1] is exactly 1.
    const double exact = 1.0;

    std::println("{:>8}{:>16}{:>16}", "n", "err trapezoid", "err simpson");

    for (int n = 4; n <= 256; n *= 2)
    {
        double t = trapezoidal(x_exp_x, 0.0, 1.0, n);
        double s = simpson(x_exp_x, 0.0, 1.0, n);
        std::println("{:>8}{:>16.3e}{:>16.3e}", n, std::abs(t - exact), std::abs(s - exact));
    }

    std::println("\nIntegral of damped oscillation on [0, 10]: {}",
                 simpson(damped_oscillation, 0.0, 10.0, 1000));

    return 0;
}
