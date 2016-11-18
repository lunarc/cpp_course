#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

extern "C" void multiply(double a[], double b[], double c[], int a_rows, int a_cols, int b_rows, int b_cols);

int main()
{
    mat a = randu<mat>(5,5);
    mat b = randu<mat>(5,5);
    mat c(5,5);

    cout << "a = " << endl;
    a.print();
    cout << "b = " << endl;
    b.print();
    
    multiply(a.memptr(), b.memptr(), c.memptr(), a.n_rows, a.n_cols, b.n_rows, b.n_cols);

    cout << "c = " << endl;
    c.print();
}
