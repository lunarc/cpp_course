#include <Eigen/Dense>
#include <print>
#include <egcpp/utils_print.h>

#include "calfem_eig.h"

int main()
{
    using Eigen::VectorXd;
    using Eigen::MatrixXd;

    VectorXd ex(2);
    VectorXd ey(2);
    VectorXd ep(2);

    ex << 0.0, 1.0;
    ey << 0.0, 1.0;
    ep << 1.0, 1.0;

    MatrixXd Ke = calfem::bar2e(ex, ey, ep);

    utils::print("Ke", Ke);
}
