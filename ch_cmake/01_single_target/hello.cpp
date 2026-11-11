#include <cmath>
#include <print>

int main()
{
    // Approximate sqrt(2) with Newton's method: x_{n+1} = (x_n + 2/x_n) / 2

    double x = 1.0;

    for (int i = 0; i < 6; ++i)
    {
        x = 0.5 * (x + 2.0 / x);
        std::print("Iteration {}: x = {}\n", i + 1, x);
    }

    std::print("Error compared to std::sqrt(2): {}\n", std::abs(x - std::sqrt(2.0)));
    std::print("Final approximation: x = {}\n", x);

    return 0;
}
