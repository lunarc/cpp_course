#include <ode/solvers.h>

#include <cmath>
#include <print>

int main()
{
    // Undamped harmonic oscillator x'' = -omega^2 x written as a system
    // y = [x, v], y' = [v, -omega^2 x].
    const double omega = 2.0;
    ode::RHS f = [omega](double, const ode::State& y) {
        return ode::State{y[1], -omega * omega * y[0]};
    };

    const double h = 0.05;
    const int n_steps = 200; // integrate to t = 10

    ode::State y_euler = {1.0, 0.0};
    ode::State y_rk4 = {1.0, 0.0};

    double t = 0.0;
    for (int i = 0; i < n_steps; ++i)
    {
        y_euler = ode::euler_step(f, t, y_euler, h);
        y_rk4 = ode::rk4_step(f, t, y_rk4, h);
        t += h;
    }

    const double exact = std::cos(omega * t);

    std::println("x({:.1f}) exact : {:9.6f}", t, exact);
    std::println("x({:.1f}) Euler : {:9.6f}  error {:.2e}", t, y_euler[0], std::abs(y_euler[0] - exact));
    std::println("x({:.1f}) RK4   : {:9.6f}  error {:.2e}", t, y_rk4[0], std::abs(y_rk4[0] - exact));

    return 0;
}
