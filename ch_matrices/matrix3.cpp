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
    
    ex << 0.0 << 1.0;
    ey << 0.0 << 1.0;
    ep << 1.0 << 1.0;
    
    mat Ke = bar2e(ex, ey, ep);
    
    cout << Ke << endl;
}