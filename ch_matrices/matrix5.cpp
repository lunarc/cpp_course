#include <iostream>
#include <cmath>
#include <armadillo>
#include <set>

#include "calfem.h"

using namespace std;
using namespace arma;

int main()
{
    // Element topology
    
    imat edof(10,4);
    
    edof << 1 << 2 << 5 << 6 << endr
         << 3 << 4 << 7 << 8 << endr
         << 5 << 6 << 9 << 10 << endr
         << 7 << 8 << 11 << 12<< endr
         << 7 << 8 << 5 << 6 << endr
         << 11 << 12 << 9 << 10 << endr
         << 3 << 4 << 5 << 6 << endr
         << 7 << 8 << 9 << 10 << endr
         << 1 << 2 << 7 << 8 << endr
         << 5 << 6 << 11 << 12 << endr;
    
    edof -= 1;
    
    // Stiffness matrix
    
    mat K(12,12);
    K.zeros();
    
    // Force vector
    
    mat f(12,1);
    f.zeros();
    f(10,0) = 0.5e6*sin(M_PI/6);
    f(11,0) = -0.5e6*cos(M_PI/6);
    
    // Material properties
    
    double A = 25.0e-4;
    double E = 2.1e11;
    
    rowvec ep(2);
    
    ep << E << A;
    
    // Element coordinates
    
    mat ex(10,2);
    mat ey(10,2);
    
    ex << 0 << 2 << endr
       << 0 << 2 << endr
       << 2 << 4 << endr
       << 2 << 4 << endr
       << 2 << 2 << endr
       << 4 << 4 << endr
       << 0 << 2 << endr
       << 2 << 4 << endr
       << 0 << 2 << endr
       << 2 << 4 << endr;
    
    ey << 2 << 2 << endr
       << 0 << 0 << endr
       << 2 << 2 << endr
       << 0 << 0 << endr
       << 0 << 2 << endr
       << 0 << 2 << endr
       << 0 << 2 << endr
       << 0 << 2 << endr
       << 2 << 0 << endr
       << 2 << 0 << endr;
    
    // Assemble system
    
    for (int i=0; i<ex.n_rows; i++)
    {
        mat Ke = bar2e(ex.row(i), ey.row(i), ep);
        assem(edof.row(i), K, Ke);
    }
    
    // Boundary conditions
        
    irowvec bcDofs(4);
    bcDofs << 0 << 1 << 2 << 3;
    
    rowvec bcValues(4);
    bcValues << 0.0 << 0.0 << 0.0 << 0.0;
    
    // Solution displacment and reaction vector
    
    mat a(K.n_rows, 1);
    mat r(K.n_rows, 1);
    
    // Solve equation system
    
    solveq(K, f, bcDofs, bcValues, a, r);
    
    // Displa
    
    cout.precision(11);
    cout.setf(ios::fixed);
    
    cout << "a =" << endl;
    a.raw_print();
    
    cout << "r =" << endl;
    r.raw_print();
    
    // Extract element displacements
    
    mat ed;
    
    extractEldisp(edof, a, ed);
    
    cout << "ed = " << endl;
    ed.raw_print();
    
    // Calculate element forces
    
    rowvec N(edof.n_rows);
    
    for (int i=0; i<edof.n_rows; i++)
        N(i) = bar2s(ex.row(i), ey.row(i), ep, ed.row(i));
    
    cout << "N = " << endl;
    N.raw_print();
    
}