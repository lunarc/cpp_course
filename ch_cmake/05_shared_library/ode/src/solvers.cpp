#include <ode/solvers.h>

namespace ode {

namespace {

// y + a * k, element by element. Lives in an anonymous namespace and is
// therefore not visible outside the library.
State axpy(const State& y, double a, const State& k)
{
    State result(y.size());
    for (std::size_t i = 0; i < y.size(); ++i)
        result[i] = y[i] + a * k[i];
    return result;
}

} // namespace

State euler_step(const RHS& f, double t, const State& y, double h)
{
    return axpy(y, h, f(t, y));
}

State rk4_step(const RHS& f, double t, const State& y, double h)
{
    const State k1 = f(t, y);
    const State k2 = f(t + h / 2, axpy(y, h / 2, k1));
    const State k3 = f(t + h / 2, axpy(y, h / 2, k2));
    const State k4 = f(t + h, axpy(y, h, k3));

    State result(y.size());
    for (std::size_t i = 0; i < y.size(); ++i)
        result[i] = y[i] + h / 6.0 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
    return result;
}

} // namespace ode
