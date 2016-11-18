#include <iostream>

using namespace std;

void simple(int* a)
{
    a[3] = 42;
}

int main()
{
    int a[] = { 1, 2, 3, 4 };
    simple(a);
    cout << "a[3] = " << a[3] << endl;
}
