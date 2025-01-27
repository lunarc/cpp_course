#include <Eigen/Dense>
#include <iostream>
#include <omp.h>

using namespace Eigen;
using namespace std;

int main()
{
    MatrixXd A(10, 10);
    A.setRandom();

    cout << "Number of threads: " << omp_get_max_threads() << "\n\n";

#pragma omp parallel for
    for (int i = 0; i < A.rows(); i++)
    {
        for (int j = 0; j < A.cols(); j++)
        {
            A(i, j) = omp_get_thread_num();
        }
    }

    cout << A << endl;
}
