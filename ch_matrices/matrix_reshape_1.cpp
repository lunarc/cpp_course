#include <print>

#include <Eigen/Dense>

#include <egcpp/utils_print.h>

int main()
{
    using Eigen::Matrix3d;
    using Eigen::MatrixXd;

    Matrix3d A;

    A << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;

    auto B = A.reshaped(1, 9);

    utils::print("B =", B);

    MatrixXd C = B.reshaped(3, 3);

    utils::print("C =", C);

    MatrixXd D = C.reshaped(1, 9).transpose();

    utils::print("D =", D);

    C = C.reshaped(1, 9).eval();

    utils::print("C =", C);

    return 0;
}
