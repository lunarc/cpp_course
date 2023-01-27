#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <set>
#include <numbers>

#include "calfem_eig.h"

using namespace std;
using namespace Eigen;

//constexpr auto PI = 3.14159265358979323846;
constexpr auto PI = std::numbers::pi;

int main()
{
    // Element topology
    
    MatrixXi edof(10,4);
    
    edof << 1,  2,  5,  6,
            3,  4,  7,  8,
            5,  6,  9,  10,
            7,  8,  11, 12,
            7,  8,  5,  6,
            11, 12, 9,  10,
            3,  4,  5,  6,
            7,  8,  9,  10,
            1,  2,  7,  8,
            5,  6,  11, 12;

    edof.array() = edof.array() - 1;
    
    // Stiffness matrix
    
    MatrixXd K(12,12);
    K = MatrixXd::Zero(12,12);
    
    // Force vector
    
    MatrixXd f(12,1);
    f = MatrixXd::Zero(12,1);

    f(10,0) = 0.5e6*sin(PI/6);
    f(11,0) = -0.5e6*cos(PI/6);
    
    // Material properties
    
    double A = 25.0e-4;
    double E = 2.1e11;
    
    VectorXd ep(2);
    
    ep << E, A;
    
    // Element coordinates
    
    MatrixXd ex(10,2);
    MatrixXd ey(10,2);
    
    ex << 0, 2,
          0, 2,
          2, 4,
          2, 4,
          2, 2,
          4, 4,
          0, 2,
          2, 4,
          0, 2,
          2, 4;
    
    ey << 2, 2,
          0, 0,
          2, 2,
          0, 0,
          0, 2,
          0, 2,
          0, 2,
          0, 2,
          2, 0,
          2, 0;

    // Assemble system
    
    for (int i=0; i<ex.rows(); i++)
    {
        MatrixXd Ke = bar2e(ex.row(i), ey.row(i), ep);
        assem(edof.row(i), K, Ke);
    }
    
    // Boundary conditions
        
    VectorXi bcDofs(4);
    bcDofs << 0, 1, 2, 3;
    
    VectorXi bcValues(4);
    bcValues << 0, 0, 0, 0;
    
    // Solution displacment and reaction vector
    
    MatrixXd a(K.rows(), 1);
    MatrixXd r(K.rows(), 1);

    a = MatrixXd::Zero(K.rows(),1);
    r = MatrixXd::Zero(K.rows(),1);

    // Solve equation system
    
    solveq(K, f, bcDofs, bcValues, a, r);
    
    // Display results
    
    cout.precision(11);
    cout.setf(ios::fixed);
    
    cout << "a =" << a << endl;
    cout << "r =" << r << endl;
    
    // Extract element displacements
    
    MatrixXd ed;
    
    extractEldisp(edof, a, ed);
    
    cout << "ed = " << ed << endl;
    
    // Calculate element forces
    
    VectorXd N(edof.rows());
    
    for (int i=0; i<edof.rows(); i++)
        N(i) = bar2s(ex.row(i), ey.row(i), ep, ed.row(i));
    
    cout << "N = " << N << endl;
}
