#include <iostream>

using namespace std;

int main()
{
    int a;
    unsigned int b;
    long int c;
    unsigned long int d;
    
    a = -1; b = -1;
    c = -1; d = -1;
    
    cout << "a = " << a << ", sizeof(a) = " << sizeof(a) << endl;
    cout << "b = " << b << ", sizeof(b) = " << sizeof(b) << endl;
    cout << "c = " << c << ", sizeof(c) = " << sizeof(c) << endl;
    cout << "d = " << d << ", sizeof(d) = " << sizeof(d) << endl;
}
