#include "integration.h"

double trapezoidal(const std::function<double(double)>& f, double a, double b, int n)
{
    const double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; ++i)
        sum += f(a + i * h);

    return h * sum;
}

double simpson(const std::function<double(double)>& f, double a, double b, int n)
{
    if (n % 2 != 0)
        ++n; // Simpson's rule needs an even number of intervals

    const double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; ++i)
        sum += (i % 2 == 0 ? 2.0 : 4.0) * f(a + i * h);

    return h * sum / 3.0;
}
