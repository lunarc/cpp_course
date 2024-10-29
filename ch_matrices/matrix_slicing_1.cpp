#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

int main()
{
    MatrixXd A(10, 10);
    A.setZero();

    A.row(3) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;

    cout << A << endl;
    cout << "\n";

    A.col(3) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;

    cout << A << endl;
    cout << "\n";

    MatrixXd B(10, 10);
    B.setZero();

    B(seq(3, 5), seq(3, 5)).setConstant(1);

    cout << B << endl;
    cout << "\n";

    B(seq(0, 9, 2), seq(0, 9, 2)).setConstant(2);

    cout << B << endl;
    cout << "\n";

    B(all, last).setConstant(3);

    cout << B << endl;
    cout << "\n";

    B(all, last - 1).setConstant(4);

    cout << B << endl;
    cout << "\n";

    VectorXd v(100);
    v.setLinSpaced(100, 1, 100);

    MatrixXd C(10, 10);
    C.reshaped(100, 1).col(0) = v;
    cout << C << endl;
    cout << "\n";

    vector<int> idx = { 1, 3, 4, 6, 7, 9 };

    cout << C(idx, idx) << endl;
    cout << "\n";

    auto D = C(idx, idx);

    return 0;
}
