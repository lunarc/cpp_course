#include <iostream>
#include <armadillo>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main()
{
    MatrixXd A = MatrixXd::Random(4,5);
    MatrixXd B = MatrixXd::Random(4,5);
    
    cout << A*B.transpose() << endl;
}
