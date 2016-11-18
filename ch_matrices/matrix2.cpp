#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

enum TAnalysisType {PLANE_STRESS, PLANE_STRAIN};

mat hooke(TAnalysisType ptype, double E, double v)
{
    mat D;
    switch (ptype) {
        case PLANE_STRESS:
            D.resize(3,3);
            D << 1.0 << v   << 0.0 << endr
              << v   << 1.0 << 0.0 << endr
              << 0.0 << 0.0 << (1.0-v)*0.5 << endr;
            break;
        case PLANE_STRAIN:
            D.resize(4,4);
            D << 1.0-v << v     << v     << 0.0 << endr
              << v     << 1.0-v << v     << 0.0 << endr
              << v     << v     << 1.0-v << 0.0 << endr
              << 0.0   << 0.0   << 0.0   << 0.5*(1.0-2*v) << endr;
            break;
        default:
            break;
    }
    return D;
}

int main()
{
    mat Dpstress = hooke(PLANE_STRESS, 2.1e9, 0.35);
    mat Dpstrain = hooke(PLANE_STRAIN, 2.1e9, 0.35);
    
    cout << "D,pstress = " << endl;
    Dpstress.print();
    cout << "D,pstrain = " << endl;
    Dpstrain.print();
}