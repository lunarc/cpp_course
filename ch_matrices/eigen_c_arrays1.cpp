#include <Eigen/Dense>
#include <print>
#include <memory>

#include <egcpp/utils_print.h>

void foo(double **data, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            std::print("{:.4f} ", data[i][j]);
        std::println();
    }
}

int main()
{
    using Eigen::MatrixXd;
    MatrixXd A(10, 10);
    A.setRandom();

    auto data = A.data();

    auto data2D = std::make_unique< double *[] >(A.rows());

    for (auto i = 0; i < A.rows(); i++)
        data2D[i] = data + i * A.cols();

    // data2D[i] = const_cast< double * >(A.row(i).data());
    // data2D[i] = A.row(i).data(); // Could give an overrun warning
    // data2D[i] = data + i * A.cols();

    foo(data2D.get(), A.rows(), A.cols());
}
