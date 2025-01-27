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

    double *data = A.data();

#pragma omp parallel for
    for (int i = 0; i < A.size(); i++)
    {
        data[i] = omp_get_thread_num();
    }

    cout << A << endl;
}
