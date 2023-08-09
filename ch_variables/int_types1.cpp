#include <iostream>

using namespace std;

int main()
{
    int a;
    unsigned int b;
    long int c;
    unsigned long int d;

    a = -1;
    b = -1; // What happens here?
    c = -1;
    d = -1; // and here?

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
}
