#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

void foo(double **data, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << data[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    MatrixXd A(10, 10);
    A.setRandom();

    double *data = A.data();
    double **data2D = new double *[A.rows()];

    for (size_t i = 0; i < A.rows(); i++)
        data2D[i] = A.row(i).data();

    // data2D[i] = const_cast< double * >(A.row(i).data());
    // data2D[i] = A.row(i).data(); // Could give an overrun warning
    // data2D[i] = data + i * A.cols();

    foo(data2D, A.rows(), A.cols());

    delete[] data2D;
}
