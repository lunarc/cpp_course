#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

using namespace std;

double f(double x)
{
    return x*x;
}

double F(double x)
{
    return x*x*x/3.0;
}

int main()
{
    int n = 100;
    double a = -1.0;
    double b = 1.0;

    cout << 1/2 << endl;
    cout << double(1) / double(2);

    return 0;
}
