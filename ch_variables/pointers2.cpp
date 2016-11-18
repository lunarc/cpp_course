#include <iostream>

using namespace std;

int main()
{
    int a[] = {0, 1, 2, 3};
    int* b;
    int* c;
    
    b = a;
    
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a[0] = " << a[0] << endl;
    cout << "b[0] = " << b[0] << endl;
    cout << "*b = " << *b << endl;
    cout << "*a = " << *a << endl;
    
    c = &a[2];

    cout << "c = " << c << endl;
    cout << "*c = " << *c << endl;
}
