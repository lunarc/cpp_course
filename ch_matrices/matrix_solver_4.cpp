#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

int main()
{
    MatrixXd A(10, 10);
    A.setRandom();

    MatrixXd b(10, 10);
    b.setRandom();

    FullPivLU<MatrixXd> ldlt(A);
    MatrixXd x = ldlt.solve(b);

    cout << "The solution is:\n"
         << x << endl;

    cout << "b is:\n"
         << b << endl;

    cout << "A * x is:\n"
         << A * x << endl;

    cout << "The error is:\n"
         << (A * x - b).norm() << endl;
}
