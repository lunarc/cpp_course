#include <iostream>

using namespace std;

int main()
{
    int a[2];
    
    a[0] = 1;
    a[1] = 2;
    
    cout << a[0] << ", " << a[1] << endl;
     
    double b[] = { 1.0, 2.0, 3.0, 4.0 };
    b[3] = 42.0;
    
    cout << b[0] << ", " << b[1] << ", " << b[2] << ", " << b[3] << endl;
}
