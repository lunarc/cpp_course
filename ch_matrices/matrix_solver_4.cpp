#include <Eigen/Dense>
#include <print>
#include <egcpp/utils_print.h>

int main()
{
    using Eigen::MatrixXd;
    using Eigen::FullPivLU;

    MatrixXd A(10, 10);
    A.setRandom();

    MatrixXd b(10, 10);
    b.setRandom();

    FullPivLU<MatrixXd> ldlt(A);
    MatrixXd x = ldlt.solve(b);

    utils::print("The solution is", x);
    utils::print("b is", b);
    utils::print("A * x is", A * x);

    std::print("The error is:\n{}\n", (A * x - b).norm());
}
