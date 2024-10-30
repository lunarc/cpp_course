#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

int main()
{
    Matrix3d A;

    A << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;

    auto B = A.reshaped(1, 9);

    cout << B << endl;

    MatrixXd C = B.reshaped(3, 3);

    cout << C << endl;

    MatrixXd D = C.reshaped(1, 9).transpose();

    cout << D << endl;

    C = C.reshaped(1, 9).eval();

    cout << C << endl;

    return 0;
}
