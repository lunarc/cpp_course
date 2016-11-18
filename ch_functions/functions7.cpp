#include <iostream>

using namespace std;

void simple(int* a)
{
    for (int i=0; i<4; i++)
        cout << a[i] << ", ";
    cout << endl;
}

int main()
{
    int a[] = { 1, 2, 3, 4 };
    simple(a);
}
