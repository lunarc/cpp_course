#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

int main()
{
    Matrix3d A;

    cout << "Here is the matrix A (uninitialised):\n"
         << A << endl;

    A.setOnes();

    cout << "Here is the matrix A:\n"
         << A << endl;

    Matrix3i B = Matrix3i::Zero();

    cout << "Here is the matrix B:\n"
         << B << endl;

    Matrix3f C;
    C.setIdentity();

    cout << "Here is the matrix C:\n"
         << C << endl;

    Matrix3d D;

    D << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;

    cout << "Here is the matrix D:\n"
         << D << endl;

    D.col(0) << 1, 2, 3;
    D.col(1) << 4, 5, 6;
    D.col(2) << 7, 8, 9;

    cout << "Here is the matrix D:\n"
         << D << endl;

    Matrix<double, 6, 3> E;

    E.col(0) << 1, 2, 3, 4, 5, 6;
    E.col(1) << 7, 8, 9, 10, 11, 12;
    E.col(2) << 13, 14, 15, 16, 17, 18;

    cout << "Here is the matrix E:\n"
         << E << endl;

    Matrix<int, 3, 6> F;

    F.row(0) << 1, 2, 3, 4, 5, 6;
    F.row(1) << 7, 8, 9, 10, 11, 12;
    F.row(2) << 13, 14, 15, 16, 17, 18;

    cout << "Here is the matrix F:\n"
         << F << endl;

    Vector<double, 3> v;

    v << 1, 2, 3;

    cout << "Here is the vector v:\n"
         << v << endl;

    Vector3d w(1, 2, 3);

    cout << "Here is the vector w:\n"
         << w << endl;

    Matrix<double, Dynamic, Dynamic> A_dyn(3, 3); // Shorthand for MatrixXd

    A_dyn << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;

    cout << "Here is the matrix A_dyn:\n"
         << A_dyn << endl;

    A_dyn.resize(1, 9); // No reallocation

    cout << "Here is the matrix A_dyn after resizing:\n"
         << A_dyn << endl;

    A_dyn.resize(6, 6); // Reallocation.

    cout << "Here is the matrix A_dyn after resizing:\n"
         << A_dyn << endl;

    A_dyn.setZero();

    cout << "Here is the matrix A_dyn after setting to zero:\n"
         << A_dyn << endl;

    Matrix<int, Dynamic, 3> B_dyn;

    B_dyn.resize(10, 3);

    B_dyn.setRandom();

    cout << "Here is the matrix B_dyn:\n"
         << B_dyn << endl;

    RowVector3d v_row(1.0, 2.0, 3.0);

    cout << "Here is the row vector v_row:\n"
         << v_row << endl;

    Vector3d v_col(1.0, 2.0, 3.0);

    cout << "Here is the row vector v_col:\n"
         << v_col << endl;
}
