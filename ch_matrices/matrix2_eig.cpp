#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

enum TAnalysisType {PLANE_STRESS, PLANE_STRAIN};

MatrixXd hooke(TAnalysisType ptype, double E, double v)
{
    MatrixXd D;
    switch (ptype) {
        case PLANE_STRESS:
            D.resize(3,3);
            D << 1.0, v,   0.0,
                 v,   1.0, 0.0,
                 0.0, 0.0, (1.0-v)*0.5;
            break;
        case PLANE_STRAIN:
            D.resize(4,4);
            D << 1.0-v, v    , v     , 0.0,
                 v    , 1.0-v, v     , 0.0,
                 v    , v    , 1.0-v , 0.0,
                 0.0  , 0.0  , 0.0   , 0.5*(1.0-2*v);
            break;
        default:
            break;
    }
    return D;
}

int main()
{
    MatrixXd Dpstress = hooke(PLANE_STRESS, 2.1e9, 0.35);
    MatrixXd Dpstrain = hooke(PLANE_STRAIN, 2.1e9, 0.35);
    
    cout << "D,pstress = " << endl;
    cout << Dpstress << endl;
    cout << "D,pstrain = " << endl;
    cout << Dpstrain << endl;
}
