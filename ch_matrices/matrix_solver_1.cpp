#include <print>

#include <Eigen/Dense>

#include <egcpp/utils_print.h>

int main()
{
    using Eigen::Matrix3d;
    using Eigen::Vector3d;

    Matrix3d A;
    A.setRandom();

    Vector3d b;

    b.setRandom();

    Vector3d x = A.inverse() * b;

    utils::print("The solution is:", x);

    utils::print("b is:", b);

    utils::print("A * x is:", A * x);

    std::println("The error is: {:.8e}", (A * x - b).norm());
}
