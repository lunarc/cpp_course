#include <iostream>

using namespace std;

void print_array_1(int* a)
{
    for (int i=0; i<4; i++)
        cout << a[i] << ", ";
    cout << endl;
}

void print_array_2(int a[])
{
    for (int i=0; i<4; i++)
        cout << a[i] << ", ";
    cout << endl;
}

int main()
{
    int a[] = { 1, 2, 3, 4 };
    print_array_1(a);
    print_array_2(a);
}
