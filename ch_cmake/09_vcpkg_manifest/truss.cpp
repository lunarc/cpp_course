// A small 2D truss solver. The geometry, material and loads are read
// from a JSON file (nlohmann::json) and the resulting linear system is
// solved with Eigen.

#include <Eigen/Dense>
#include <nlohmann/json.hpp>

#include <array>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <print>
#include <string>
#include <vector>

using json = nlohmann::json;

int main(int argc, char* argv[])
{
    const char* filename = argc > 1 ? argv[1] : "truss.json";

    std::ifstream file(filename);
    if (!file)
    {
        std::println(stderr, "Could not open {}", filename);
        return 1;
    }

    const json input = json::parse(file);

    const double E = input["E"];
    const double A = input["A"];
    const auto nodes = input["nodes"].get<std::vector<std::array<double, 2>>>();
    const auto bars = input["bars"].get<std::vector<std::array<int, 2>>>();
    const auto fixed = input["fixed_dofs"].get<std::vector<int>>();

    std::println("{}\n", input["description"].get<std::string>());

    // Two degrees of freedom (x, y) per node.
    const int n_dofs = 2 * static_cast<int>(nodes.size());
    Eigen::MatrixXd K = Eigen::MatrixXd::Zero(n_dofs, n_dofs);
    Eigen::VectorXd f = Eigen::VectorXd::Zero(n_dofs);

    // Assemble the global stiffness matrix bar by bar.
    for (const auto& [n1, n2] : bars)
    {
        const double dx = nodes[n2][0] - nodes[n1][0];
        const double dy = nodes[n2][1] - nodes[n1][1];
        const double L = std::hypot(dx, dy);
        const double c = dx / L, s = dy / L;

        Eigen::Vector4d g(-c, -s, c, s);
        Eigen::Matrix4d Ke = E * A / L * g * g.transpose();

        const int dofs[4] = {2 * n1, 2 * n1 + 1, 2 * n2, 2 * n2 + 1};
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                K(dofs[i], dofs[j]) += Ke(i, j);
    }

    for (const auto& load : input["loads"])
    {
        const int node = load["node"];
        f(2 * node) += load["fx"].get<double>();
        f(2 * node + 1) += load["fy"].get<double>();
    }

    // Apply boundary conditions by replacing rows/columns of fixed dofs.
    for (int dof : fixed)
    {
        K.row(dof).setZero();
        K.col(dof).setZero();
        K(dof, dof) = 1.0;
        f(dof) = 0.0;
    }

    const Eigen::VectorXd u = K.ldlt().solve(f);

    std::println("Node displacements [mm]:");
    for (std::size_t i = 0; i < nodes.size(); ++i)
        std::println("  node {}: ux = {:8.4f}, uy = {:8.4f}", i, 1000.0 * u(2 * i),
                     1000.0 * u(2 * i + 1));

    // Bar forces computed from the elongation of each bar.
    std::println("\nBar forces [kN] (positive = tension):");
    for (std::size_t b = 0; b < bars.size(); ++b)
    {
        const auto [n1, n2] = bars[b];
        const double dx = nodes[n2][0] - nodes[n1][0];
        const double dy = nodes[n2][1] - nodes[n1][1];
        const double L = std::hypot(dx, dy);
        const double c = dx / L, s = dy / L;

        const double elongation =
            c * (u(2 * n2) - u(2 * n1)) + s * (u(2 * n2 + 1) - u(2 * n1 + 1));
        std::println("  bar {}: {:8.3f}", b, E * A / L * elongation / 1000.0);
    }

    return 0;
}
