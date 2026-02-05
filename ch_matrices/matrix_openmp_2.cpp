#include <print>

#include <Eigen/Dense>
#include <omp.h>

#include <egcpp/utils_print.h>

int main()
{
    using Eigen::MatrixXd;

    MatrixXd A(10, 10);
    A.setRandom();

    std::println("Number of threads: {}", omp_get_max_threads());

#pragma omp parallel for
    for (int i = 0; i < A.rows(); i++)
    {
        for (int j = 0; j < A.cols(); j++)
        {
            A(i, j) = omp_get_thread_num();
        }
    }

    utils::print("A", A);
}
