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

    auto data = A.data();

#pragma omp parallel for
    for (int i = 0; i < A.size(); i++)
    {
        data[i] = omp_get_thread_num();
    }

    utils::print("A =", A);
}
