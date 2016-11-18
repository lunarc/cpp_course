#include <iostream>

using namespace std;

void simple(int a)
{
    cout << "The value of a = " << a << endl;
    cout << "&a = " << &a << endl;
}

int main()
{
    int a = 42;
    simple(a);
    
    cout << "&a = " << &a << endl;
}
