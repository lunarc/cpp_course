#include <iostream>

using namespace std;

int main()
{
    int a, b, c;
    double d, e;
    
    a = 40;
    b = 2;
    d = 52.5654;
    
    // d will be truncated
    c = a + b + d;
    
    // a and be will be upcasted to double
    e = a + b + d;
    
    cout << "c = a + b + d = " << c << endl;
    cout << "e = a + b + d = " << e << endl;
}
