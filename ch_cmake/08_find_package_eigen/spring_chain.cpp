// A chain of n springs fixed at the left end and loaded with a force F
// at the right end. Assembling the stiffness matrix K and solving
// K u = f gives the displacement u of every node.

#include <Eigen/Dense>

#include <print>

int main()
{
    const int n_springs = 5;
    const double k = 1000.0; // spring stiffness [N/m]
    const double F = 50.0;   // applied force [N]

    // Nodes 1..n are free, node 0 is fixed, so we have n unknowns.
    Eigen::MatrixXd K = Eigen::MatrixXd::Zero(n_springs, n_springs);

    for (int e = 0; e < n_springs; ++e)
    {
        // Spring e connects node e and node e + 1. Shift by -1 because
        // the fixed node 0 has been removed from the system.
        const int i = e - 1;
        const int j = e;

        if (i >= 0)
        {
            K(i, i) += k;
            K(i, j) -= k;
            K(j, i) -= k;
        }
        K(j, j) += k;
    }

    Eigen::VectorXd f = Eigen::VectorXd::Zero(n_springs);
    f(n_springs - 1) = F;

    // K is symmetric positive definite, so a Cholesky factorisation works.
    Eigen::VectorXd u = K.llt().solve(f);

    // Eigen matrices cannot be passed directly to std::print, so the
    // elements are printed one by one.
    std::println("Stiffness matrix K [N/m]:");
    for (int r = 0; r < K.rows(); ++r)
    {
        for (int c = 0; c < K.cols(); ++c)
            std::print("{:8.0f}", K(r, c));
        std::println();
    }

    std::println("\nDisplacements u [mm]:");
    for (int r = 0; r < u.size(); ++r)
        std::println("  node {}: {:6.1f}", r + 1, 1000.0 * u(r));

    std::println("\nExpected tip displacement: {:.1f} mm", 1000.0 * n_springs * F / k);

    return 0;
}
