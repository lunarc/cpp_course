#pragma once

#include <vector>

namespace heat {

// Solves the 1D heat equation  du/dt = alpha * d2u/dx2  on [0, L] with
// fixed temperatures at both ends, using the explicit FTCS scheme.
class Heat1D
{
public:
    Heat1D(int n_points, double length, double alpha);

    void set_initial(const std::vector<double>& u0);
    void set_boundary(double left, double right);

    // Largest time step for which the explicit scheme is stable.
    double max_stable_dt() const;

    void step(double dt);
    void advance(double t_end, double dt);

    const std::vector<double>& temperature() const { return m_u; }
    double dx() const { return m_dx; }
    double time() const { return m_time; }

private:
    double m_dx;
    double m_alpha;
    double m_time = 0.0;
    std::vector<double> m_u;
    std::vector<double> m_u_new;
};

} // namespace heat
