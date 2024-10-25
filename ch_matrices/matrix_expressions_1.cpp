#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main()
{
    Matrix3d A;

    A << 1, 2, 3,
		 4, 5, 6,
		 7, 8, 9;

    Matrix3d B;

    B << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;

    auto C = A + B;
	cout << C << endl;

    auto D = A * 3.0;
    cout << D << endl;

    auto E = A * B;
    cout << E << endl;

    auto F = E + Matrix3d::Constant(1.0);   
    cout << F << endl;

    Matrix3d G = E.array() + 3.0;
    cout << G << endl;

    Matrix3d H;

    H << 1, 2, 3,
		 4, 5, 6,
		 7, 8, 9;

    std::cout << "H^T = " << std::endl << H.transpose() << std::endl;

    Vector3d s(1, 2, 3);
    Vector3d t(1, 0, 0);

    auto u = s.cross(t);
    auto p = s.dot(t);

    cout << u << endl;
    cout << p << endl;

    Matrix3d J;

    J << 15, 42, 71,
         23, 52, 81,
         33, 63, 91;

    cout << J.inverse() << endl;

    Matrix3d K;

    K << 1, 2, 3,
		 4, 5, 6,
		 7, 8, 9;

    cout << "K.sum()\n" << K.sum() << endl;
    cout << "K.prod()\n" << K.prod() << endl;
    cout << "K.mean()\n" << K.mean() << endl;
    cout << "K.norm()\n" << K.norm() << endl;
    cout << "K.maxCoeff()\n" << K.maxCoeff() << endl;
    cout << "K.minCoeff()\n" << K.minCoeff() << endl;
    cout << "K.trace()\n" << K.trace() << endl;
    cout << "K.diagonal()\n" << K.diagonal() << endl;
    cout << "K.determinant()\n" << K.determinant() << endl;

	return 0;

}
