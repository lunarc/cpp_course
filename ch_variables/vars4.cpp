#include <iostream>

using namespace std;

int main()
{
    int a[] = {1,2,3,4};
    
    a[3] = 42;
    
    cout << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << endl;
}
