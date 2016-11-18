#include <iostream>

using namespace std;

int main()
{
    int a, b, c;
    
    a = 42;
    
    b = ++a;
    c = a++;
    
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
}