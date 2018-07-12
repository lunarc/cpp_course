#include <iostream>
#include <Eigen/Dense>

#include "calfem_eig.h"

using namespace std;
using namespace Eigen;

int main()
{
    VectorXd ex(2);
    VectorXd ey(2);
    VectorXd ep(2);
    VectorXd ed(4);
    
    ex << 0.0, 1.0;
    ey << 0.0, 1.0;
    ep << 1.0, 1.0;
    ed << 0.0, 0.0, 0.01, 0.01;
    
    MatrixXd Ke = bar2e(ex, ey, ep);
    cout << "Ke=" << endl;
    cout << Ke << endl;
    
    double N = bar2s(ex, ey, ep, ed);
    
    cout << "N = " << N << endl;
}
