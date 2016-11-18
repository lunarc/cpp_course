#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	double pi = 4 * std::atan(1);
    double x = 0.0;
    double dx = 0.1;
    
    cout << setw(15) << left << "X";
    cout << setw(10) << right << "f(x)" << endl;
    cout << setfill('-');
    cout << setw(25) << "" << endl;
    cout << setfill(' ');
    cout << setprecision(6) << fixed;
    //cout.unsetf(ios_base::fixed);
    
    while (x<=pi*0.25)
    {
        cout << setw(15) << left << x;
        cout << setw(10) << right << sin(x);
        cout << endl;
        x += dx;
    }
}