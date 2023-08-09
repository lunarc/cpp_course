#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

extern "C" void multiply(double a[], double b[], double c[], int a_rows, int a_cols, int b_rows, int b_cols);

int main()
{
    MatrixXd a = MatrixXd::Random(5,5);
    MatrixXd b = MatrixXd::Random(5,5);
    MatrixXd c(5,5);

    cout << "a = " << "\n";
    cout << a << "\n";
    cout << "b = " << "\n";
    cout << b << "\n";
    
    multiply(a.data(), b.data(), c.data(), a.rows(), a.cols(), b.rows(), b.cols());

    cout << "c = " << "\n";
    cout << c << "\n";
}
