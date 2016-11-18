#include <iostream>

using namespace std;

void simple(int& a)
{
    a = 43;
}

int main()
{
    int a = 42;
    
    cout << "Before function call: a = " << a << endl;
    simple(a);
    cout << "After function call : a = " << a << endl;
}
