#include <algorithm>
#include <iostream>
#include <functional>
#include <cmath>

void tabulate_c(double x_start, double x_end, double dx, double (*f)(double))
{
    auto x = x_start;

    std::cout << "x, f(x)" << std::endl;
    std::cout << "-------------------" << std::endl;

    while (x <= x_end)
    {
        std::cout << x << ", " << f(x) << std::endl;
        x += dx;
    }
}

void tabulate(double x_start, double x_end, double dx, std::function<double(double x)> const& f)
{
    auto x = x_start;

    std::cout << "x, f(x)" << std::endl;
    std::cout << "-------------------" << std::endl;

    while (x <= x_end)
    {
        std::cout << x << ", " << f(x) << std::endl;
        x += dx;
    }
}

double q(double x)
{
    return cos(x);
}

int main()
{
    tabulate(-6.0, 6.0, 0.2, [](double x) -> double { return sin(x); });
    tabulate(-6.0, 6.0, 0.2, q);

    tabulate_c(-6.0, 6.0, 0.2, [](double x) -> double { return sin(x); });
    tabulate_c(-6.0, 6.0, 0.2, q);
}
