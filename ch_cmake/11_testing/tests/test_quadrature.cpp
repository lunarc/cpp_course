#include <quadrature.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cmath>
#include <numbers>
#include <stdexcept>

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

// Floating point results must never be compared with ==. Catch2
// provides matchers for absolute and relative tolerances.

TEST_CASE("Trapezoidal rule is exact for linear functions", "[trapezoidal]")
{
    auto f = [](double x) { return 3.0 * x + 2.0; };
    REQUIRE_THAT(quad::trapezoidal(f, 0.0, 2.0, 1), WithinAbs(10.0, 1e-12));
}

TEST_CASE("Simpson's rule is exact for cubic polynomials", "[simpson]")
{
    auto f = [](double x) { return x * x * x - 2.0 * x * x + 1.0; };
    // Integral over [0, 2] = 4 - 16/3 + 2 = 2/3
    REQUIRE_THAT(quad::simpson(f, 0.0, 2.0, 2), WithinAbs(2.0 / 3.0, 1e-12));
}

TEST_CASE("Gauss-Legendre 2-point is exact for cubic polynomials", "[gauss]")
{
    auto f = [](double x) { return x * x * x - 2.0 * x * x + 1.0; };
    REQUIRE_THAT(quad::gauss2(f, 0.0, 2.0, 1), WithinAbs(2.0 / 3.0, 1e-12));
}

TEST_CASE("Methods agree on the integral of sin(x) over [0, pi]", "[all]")
{
    auto f = [](double x) { return std::sin(x); };
    const double pi = std::numbers::pi;

    // SECTIONs share the setup code above; each one runs separately.
    SECTION("trapezoidal")
    {
        REQUIRE_THAT(quad::trapezoidal(f, 0.0, pi, 1000), WithinRel(2.0, 1e-5));
    }
    SECTION("simpson")
    {
        REQUIRE_THAT(quad::simpson(f, 0.0, pi, 100), WithinRel(2.0, 1e-7));
    }
    SECTION("gauss2")
    {
        REQUIRE_THAT(quad::gauss2(f, 0.0, pi, 100), WithinRel(2.0, 1e-7));
    }
}

TEST_CASE("Trapezoidal rule converges with order 2", "[trapezoidal][convergence]")
{
    // Halving h should reduce the error by a factor of about 2^2 = 4.
    auto f = [](double x) { return std::exp(x); };
    const double exact = std::exp(1.0) - 1.0;

    const double e1 = std::abs(quad::trapezoidal(f, 0.0, 1.0, 50) - exact);
    const double e2 = std::abs(quad::trapezoidal(f, 0.0, 1.0, 100) - exact);

    REQUIRE_THAT(std::log2(e1 / e2), WithinAbs(2.0, 0.05));
}

TEST_CASE("Simpson's rule converges with order 4", "[simpson][convergence]")
{
    auto f = [](double x) { return std::exp(x); };
    const double exact = std::exp(1.0) - 1.0;

    const double e1 = std::abs(quad::simpson(f, 0.0, 1.0, 10) - exact);
    const double e2 = std::abs(quad::simpson(f, 0.0, 1.0, 20) - exact);

    REQUIRE_THAT(std::log2(e1 / e2), WithinAbs(4.0, 0.05));
}

TEST_CASE("Invalid number of intervals throws", "[errors]")
{
    auto f = [](double x) { return x; };
    REQUIRE_THROWS_AS(quad::trapezoidal(f, 0.0, 1.0, 0), std::invalid_argument);
    REQUIRE_THROWS_AS(quad::simpson(f, 0.0, 1.0, -1), std::invalid_argument);
    REQUIRE_THROWS_AS(quad::gauss2(f, 0.0, 1.0, 0), std::invalid_argument);
}
