#include <print>
#include <Eigen/Dense>

#include <egcpp/utils_print.h>

int main()
{
    using Eigen::Matrix3d;
    using Eigen::Vector3d;

    Matrix3d A;

    A << 1, 2, 3,
		 4, 5, 6,
		 7, 8, 9;

    Matrix3d B;

    B << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;

    auto C = A + B;

    utils::print("C = A + B:", C);

    auto D = A * 3.0;
    utils::print("D = A * 3.0:", D);

    auto E = A * B;
    utils::print("E = A * B:", E);

    auto F = E + Matrix3d::Constant(1.0);
    utils::print("F = E + 1.0:", F);

    Matrix3d G = E.array() + 3.0;
    utils::print("G = E + 3.0:", G);

    Matrix3d H;

    H << 1, 2, 3,
		 4, 5, 6,
		 7, 8, 9;

    utils::print("H^T =", H.transpose());

    Vector3d s(1, 2, 3);
    Vector3d t(1, 0, 0);

    auto u = s.cross(t);
    auto p = s.dot(t);

    utils::print("u =", u);
    std::println("p = {}", p);

    Matrix3d J;

    J << 15, 42, 71,
         23, 52, 81,
         33, 63, 91;

    utils::print("J.inverse() = {}", J.inverse());

    Matrix3d K;

    K << 1, 2, 3,
		 4, 5, 6,
		 7, 8, 9;

    std::println("K.sum() = {}", K.sum());
    std::println("K.prod() = {}", K.prod());
    std::println("K.mean() = {}", K.mean());
    std::println("K.norm() = {}", K.norm());
    std::println("K.maxCoeff() = {}", K.maxCoeff());
    std::println("K.minCoeff() = {}", K.minCoeff());
    std::println("K.trace() = {}", K.trace());
    utils::print("K.diagonal() = {}", K.diagonal());
    std::println("K.determinant() = {}", K.determinant());

	return 0;

}
