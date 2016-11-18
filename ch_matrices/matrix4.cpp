#include <iostream>
#include <armadillo>

#include "calfem.h"

using namespace std;
using namespace arma;

int main()
{
    rowvec ex(2);
    rowvec ey(2);
    rowvec ep(2);
    rowvec ed(4);
    
    ex << 0.0 << 1.0;
    ey << 0.0 << 1.0;
    ep << 1.0 << 1.0;
    ed << 0.0 << 0.0 << 0.01 << 0.01;
    
    mat Ke = bar2e(ex, ey, ep);
    cout << "Ke=" << endl;
    cout << Ke << endl;
    
    double N = bar2s(ex, ey, ep, ed);
    
    cout << "N = " << N << endl;
}