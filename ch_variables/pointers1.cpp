#include <iostream>

using namespace std;

int main()
{
    int a;
    int* b;
    
    a = 42;
    b = &a;
    
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "&a = " << &a << endl;
    cout << "*b = " << *b << endl;
}
