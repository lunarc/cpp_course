#include <heat/heat1d.h>

#include <stdexcept>

namespace heat {

Heat1D::Heat1D(int n_points, double length, double alpha)
    : m_dx(length / (n_points - 1)), m_alpha(alpha), m_u(n_points, 0.0), m_u_new(n_points, 0.0)
{
    if (n_points < 3)
        throw std::invalid_argument("Heat1D needs at least 3 grid points");
}

void Heat1D::set_initial(const std::vector<double>& u0)
{
    if (u0.size() != m_u.size())
        throw std::invalid_argument("Initial condition has wrong size");
    m_u = u0;
    m_time = 0.0;
}

void Heat1D::set_boundary(double left, double right)
{
    m_u.front() = left;
    m_u.back() = right;
}

double Heat1D::max_stable_dt() const
{
    return 0.5 * m_dx * m_dx / m_alpha;
}

void Heat1D::step(double dt)
{
    const double r = m_alpha * dt / (m_dx * m_dx);
    const auto n = m_u.size();

    m_u_new.front() = m_u.front();
    m_u_new.back() = m_u.back();

    for (std::size_t i = 1; i < n - 1; ++i)
        m_u_new[i] = m_u[i] + r * (m_u[i - 1] - 2.0 * m_u[i] + m_u[i + 1]);

    m_u.swap(m_u_new);
    m_time += dt;
}

void Heat1D::advance(double t_end, double dt)
{
    while (m_time < t_end - 1e-12)
        step(dt);
}

} // namespace heat
