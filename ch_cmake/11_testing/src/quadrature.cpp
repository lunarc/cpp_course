#include <quadrature.h>

#include <cmath>
#include <stdexcept>

namespace quad {

double trapezoidal(const Function& f, double a, double b, int n)
{
    if (n < 1)
        throw std::invalid_argument("n must be at least 1");

    const double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; ++i)
        sum += f(a + i * h);
    return h * sum;
}

double simpson(const Function& f, double a, double b, int n)
{
    if (n < 1)
        throw std::invalid_argument("n must be at least 1");
    if (n % 2 != 0)
        ++n;

    const double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; ++i)
        sum += (i % 2 == 0 ? 2.0 : 4.0) * f(a + i * h);
    return h * sum / 3.0;
}

double gauss2(const Function& f, double a, double b, int n)
{
    if (n < 1)
        throw std::invalid_argument("n must be at least 1");

    const double h = (b - a) / n;
    const double offset = h / (2.0 * std::sqrt(3.0));
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        const double mid = a + (i + 0.5) * h;
        sum += f(mid - offset) + f(mid + offset);
    }
    return 0.5 * h * sum;
}

} // namespace quad
