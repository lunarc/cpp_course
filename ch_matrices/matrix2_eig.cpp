#include <Eigen/Dense>
#include <print>
#include <egcpp/utils_print.h>

enum TAnalysisType {PLANE_STRESS, PLANE_STRAIN};

Eigen::MatrixXd hooke(TAnalysisType ptype, double E, double v)
{
    Eigen::MatrixXd D;
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

    std::print("In hooke.\n");
    utils::print_addr(D);

    return D;
}

int main()
{
    using Eigen::MatrixXd;

    MatrixXd Dpstress = hooke(PLANE_STRESS, 2.1e9, 0.35);
    std::println("Back in main.");
    utils::print_addr(Dpstress);

    MatrixXd Dpstrain = hooke(PLANE_STRAIN, 2.1e9, 0.35);
    std::println("Back in main.");
    utils::print_addr(Dpstrain);
    
    utils::print("D,pstress = ", Dpstress);
    utils::print("D,pstrain = ", Dpstrain);
}
