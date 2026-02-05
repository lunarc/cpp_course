#include <print>
#include <vector>

#include <Eigen/Dense>

#include <egcpp/utils_print.h>

int main()
{
    using Eigen::MatrixXd;
    using Eigen::VectorXd;
    using Eigen::seq;
    using Eigen::all;
    using Eigen::last;

    MatrixXd A(10, 10);
    A.setZero();

    A.row(3) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;

    utils::print("A", A);

    A.col(3) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;

    utils::print("A", A);

    A.col(1).setOnes();

    utils::print("A", A);

    MatrixXd B(10, 10);
    B.setZero();

    B(seq(3, 5), seq(3, 5)).setConstant(1);

    utils::print("B", B);

    B(seq(0, 9, 2), seq(0, 9, 2)).setConstant(2);

    utils::print("B", B);

    B(all, last).setConstant(3);

    utils::print("B", B);

    B(all, last - 1).setConstant(4);

    utils::print("B", B);

    VectorXd v(100);
    v.setLinSpaced(100, 1, 100);

    MatrixXd C(10, 10);
    C.reshaped(100, 1).col(0) = v;

    utils::print("C", C);

    std::vector<int> idx = { 1, 3, 4, 6, 7, 9 };

    utils::print("C(idx, idx)", C(idx, idx));

    auto D = C(idx, idx);

    utils::print("D", D);
}
