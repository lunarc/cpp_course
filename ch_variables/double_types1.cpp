#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	double pi = 4 * std::atan(1);
	
    float f;
    double d;
    long double ld;
    
    f = pi;
    d = pi;
    ld = pi;
    
    cout << setprecision(15) << "f = " << f << endl;
    cout << setprecision(15) << "d = " << d << endl;
    cout << setprecision(15) << "ld = " << ld << endl;
}
