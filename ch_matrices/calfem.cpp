#include "calfem.h"

#include <cmath>
#include <set>

arma::mat hooke(TAnalysisType ptype, double E, double v)
{
    using namespace arma;
    
    mat D;
    switch (ptype) {
        case PLANE_STRESS:
            D.resize(3,3);
            D << 1.0 << v   << 0.0 << endr
            << v   << 1.0 << 0.0 << endr
            << 0.0 << 0.0 << (1.0-v)*0.5 << endr;
            
            D *= E/(1-v*v);
            
            break;
        case PLANE_STRAIN:
            D.resize(4,4);
            D << 1.0-v << v     << v     << 0.0 << endr
            << v     << 1.0-v << v     << 0.0 << endr
            << v     << v     << 1.0-v << 0.0 << endr
            << 0.0   << 0.0   << 0.0   << 0.5*(1.0-2*v) << endr;
            
            D *= E/((1+v)*(1-2*v));
            
            break;
        default:
            break;
    }
    return D;
}

arma::mat bar2e(arma::rowvec ex, arma::rowvec ey, arma::rowvec ep)
{
    using namespace arma;
    
    double E = ep(0);
    double A = ep(1);
    double L = sqrt(pow(ex(1)-ex(0),2)+pow(ey(1)-ey(0),2));
    double C = E*A/L;
    
    mat Ke_loc(2,2);

    Ke_loc <<  C << -C << endr
           << -C <<  C << endr;
    
    double nxx = (ex(1)-ex(0))/L;
    double nyx = (ey(1)-ey(0))/L;
    
    mat G(2,4);
    
    G << nxx << nyx << 0.0 << 0.0 << endr
      << 0.0 << 0.0 << nxx << nyx << endr;
    
    mat Ke = G.t()*Ke_loc*G;
    return Ke;
}

double bar2s(arma::rowvec ex, arma::rowvec ey, arma::rowvec ep, arma::rowvec ed)
{
    using namespace arma;
    
    double E = ep(0);
    double A = ep(1);
    double L = sqrt(pow(ex(1)-ex(0),2)+pow(ey(1)-ey(0),2));
    double C = E*A/L;
    
    double nxx = (ex(1)-ex(0))/L;
    double nyx = (ey(1)-ey(0))/L;
    
    mat G(2,4);
    
    G << nxx << nyx << 0.0 << 0.0 << endr
    << 0.0 << 0.0 << nxx << nyx << endr;

    rowvec temp;
    temp << -C << C;
    
    return as_scalar(temp * G * ed.t());
}

void assem(arma::imat topo, arma::mat& K, arma::mat& Ke)
{
    for (int row=0; row<Ke.n_rows; row++)
        for (int col=0; col<Ke.n_cols; col++)
            K(topo(row), topo(col)) += Ke(row,col);
}

void solveq(arma::mat& K, arma::mat&f, arma::irowvec& bcDofs, arma::rowvec& bcValues, arma::mat& a, arma::mat& r)
{
    using namespace std;
    using namespace arma;
    
    set<int> bc;
    
    for (int i=0; i<bcDofs.size(); i++)
        bc.insert(bcDofs(i));
    
    uvec allIndices(K.n_rows-bc.size());
    uvec colIndices;
    
    colIndices << 0;
    
    int count = 0;
    
    for (int i=0; i<K.n_rows; i++)
        if (bc.find(i)==bc.end())
            allIndices(count++) = i;
    
    mat Ksolve = K(allIndices, allIndices);
    mat fsolve = f(allIndices, colIndices);
    mat asolve = solve(Ksolve, fsolve);
    
    a.zeros();
    a(allIndices, colIndices) = asolve;
    
    /* Q=K*asmatrix(a)-f */
    
    r = K*a-f;
}

void extractEldisp(arma::imat& edof, arma::mat& a, arma::mat& ed)
{
    int nDofs = edof.n_cols;
    int nElements = edof.n_rows;
    
    ed.resize(nElements, nDofs);
    
    for (int i=0; i<nElements; i++)
        for (int j=0; j<nDofs; j++)
            ed(i,j) = a(edof(i,j),0);
}


