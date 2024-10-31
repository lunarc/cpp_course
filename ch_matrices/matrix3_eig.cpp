#include <Eigen/Dense>
#include <iostream>

#include "calfem_eig.h"

using namespace std;
using namespace Eigen;

int main()
{
    VectorXd ex(2);
    VectorXd ey(2);
    VectorXd ep(2);

    ex << 0.0, 1.0;
    ey << 0.0, 1.0;
    ep << 1.0, 1.0;

    MatrixXd Ke = bar2e(ex, ey, ep);

    cout << Ke << endl;
}
