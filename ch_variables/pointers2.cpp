#include <iostream>

using namespace std;

int main()
{
    int a[] = {0, 1, 2, 3};
    int* b;
    int* c;
    int* d;
    
    b = a;
    
    cout << "a = " << a << "\n";
    cout << "b = " << b << "\n";
    cout << "a[0] = " << a[0] << "\n";
    cout << "b[0] = " << b[0] << "\n";
    cout << "*b = " << *b << "\n";
    cout << "*a = " << *a << "\n";
    
    c = &a[2];

    cout << "c = " << c << "\n";
    cout << "*c = " << *c << "\n";

    d = b + 2;

    cout << "d = " << d << "\n";
    cout << "*d = " << *d << "\n";
}
