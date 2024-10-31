#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

int main()
{
    Matrix3d A;
    A.setRandom();

    Vector3d b;

    b.setRandom();

    Vector3d x = A.inverse() * b;

    cout << "The solution is:\n"
         << x << endl;

    cout << "b is:\n"
         << b << endl;

    cout << "A * x is:\n"
         << A * x << endl;

    cout << "The error is:\n"
         << (A * x - b).norm() << endl;
}
