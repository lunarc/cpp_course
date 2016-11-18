#include <iostream>

using namespace std;

int main()
{
    int a[] = {1,2,3,4};
    int* b;
    
    a[3] = 42;
    
    cout << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << endl;
    
    b = a;

    cout << b[0] << ", " << b[1] << ", " << b[2] << ", " << b[3] << endl;
}
