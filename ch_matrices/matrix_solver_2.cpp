#include <Eigen/Dense>
#include <print>
#include <egcpp/utils_print.h>

int main()
{
    using Eigen::MatrixXd;
    using Eigen::VectorXd;

    MatrixXd A(10, 10);
    A.setRandom();

    VectorXd b(10);
    b.setRandom();

    VectorXd x = A.colPivHouseholderQr().solve(b);

    utils::print("The solution is", x);
    utils::print("b is", b);
    utils::print("A * x is", A * x);

    std::print("The error is:\n{}\n", (A * x - b).norm());
}
