#include <heat/heat1d.h>

#include <print>

int main()
{
    // A 1 m steel rod (alpha ~ 1.2e-5 m^2/s) initially at 20 C. The left
    // end is suddenly heated to 100 C, the right end is kept at 20 C.
    const int n = 21;
    heat::Heat1D rod(n, 1.0, 1.2e-5);

    rod.set_initial(std::vector<double>(n, 20.0));
    rod.set_boundary(100.0, 20.0);

    const double dt = 0.9 * rod.max_stable_dt();

    for (double t_hours : {0.5, 2.0, 8.0, 24.0})
    {
        rod.advance(t_hours * 3600.0, dt);

        // std::print does not add a newline, so several calls build one line.
        std::print("t = {:5.1f} h: ", t_hours);
        for (std::size_t i = 0; i < rod.temperature().size(); i += 4)
            std::print("{:7.1f}", rod.temperature()[i]);
        std::println();
    }

    return 0;
}
