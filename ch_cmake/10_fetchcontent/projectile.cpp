// Projectile motion with quadratic air drag, integrated with the
// semi-implicit Euler method. All parameters can be set on the command
// line thanks to CLI11.

#include <CLI/CLI.hpp>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <numbers>
#include <ostream> // std::println(std::ostream&, ...) for writing to files
#include <print>
#include <string>

int main(int argc, char* argv[])
{
    CLI::App app{"Projectile motion with air drag"};

    double speed = 30.0;
    double angle = 45.0;
    double drag = 0.0;
    double dt = 1e-3;
    std::string output;

    app.add_option("-v,--speed", speed, "Initial speed [m/s]")->check(CLI::PositiveNumber);
    app.add_option("-a,--angle", angle, "Launch angle [degrees]")->check(CLI::Range(0.0, 90.0));
    app.add_option("-k,--drag", drag, "Drag coefficient k/m [1/m]")->check(CLI::NonNegativeNumber);
    app.add_option("--dt", dt, "Time step [s]")->check(CLI::PositiveNumber);
    app.add_option("-o,--output", output, "Write trajectory to this file");

    CLI11_PARSE(app, argc, argv);

    const double g = 9.81;
    const double theta = angle * std::numbers::pi / 180.0;

    double x = 0.0, y = 0.0, t = 0.0;
    double vx = speed * std::cos(theta);
    double vy = speed * std::sin(theta);
    double y_max = 0.0;

    std::ofstream out;
    if (!output.empty())
        out.open(output);

    while (y >= 0.0)
    {
        const double v = std::hypot(vx, vy);
        vx += -drag * v * vx * dt;
        vy += (-g - drag * v * vy) * dt;
        x += vx * dt;
        y += vy * dt;
        t += dt;

        y_max = std::max(y_max, y);
        if (out.is_open())
            std::println(out, "{} {} {}", t, x, y);
    }

    std::println("Flight time : {:.3f} s", t);
    std::println("Range       : {:.2f} m", x);
    std::println("Max height  : {:.2f} m", y_max);

    if (drag == 0.0)
        std::println("Analytical range without drag: {:.2f} m",
                     speed * speed * std::sin(2 * theta) / g);

    return 0;
}
