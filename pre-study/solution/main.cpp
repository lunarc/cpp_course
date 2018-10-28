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
    int n = 1000;
    double a = -1.0;
    double b = 1.0;

    int k=1;
    double sum = 0.0;

    while (k<n)
    {
        sum += f(a+double(k)*(b-a)/double(n));
        k++;
    }

    double int_f = (b-a)*(0.5*f(a) + sum + f(b*0.5))/double(n);

    cout << "integral of f = " << int_f << endl;

    return 0;
}
