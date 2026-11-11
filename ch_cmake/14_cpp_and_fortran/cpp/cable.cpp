// Sag of a cable under uniform load q, held with tension T between two
// supports at the same height:  T w''(x) = -q,  w(0) = w(L) = 0.
// Finite differences give a tridiagonal system that is solved by the
// Fortran routine.

#include "tridiag.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    const double L = 100.0;  // span [m]
    const double T = 5.0e4;  // cable tension [N]
    const double q = 20.0;   // distributed load [N/m]
    const int n = 99;        // number of interior points
    const double h = L / (n + 1);

    // Discretised:  w(i-1) - 2 w(i) + w(i+1) = -q h^2 / T
    std::vector<double> a(n, 1.0), b(n, -2.0), c(n, 1.0), d(n, -q * h * h / T), w(n);
    a[0] = 0.0;      // no neighbour to the left of the first point
    c[n - 1] = 0.0;  // no neighbour to the right of the last point

    solve_tridiagonal(n, a.data(), b.data(), c.data(), d.data(), w.data());

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "   x [m]    w [m]   exact [m]\n";
    for (int i = 9; i < n; i += 10)
    {
        const double x = (i + 1) * h;
        const double exact = q * x * (L - x) / (2.0 * T);
        std::cout << std::setw(8) << x << std::setw(9) << w[i] << std::setw(12) << exact << '\n';
    }

    return 0;
}
