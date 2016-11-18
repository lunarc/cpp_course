#include <iostream>

using namespace std;

int main()
{
    int* a = 0;
    int* b = 0;
    
    a = new int[10];
    
    for (int i=0; i<10; i++)
        a[i] = i;
    
    b = &a[6];
    
    cout << "a = " << a << endl;
    cout << "a[5] = " << a[5] << endl;
    cout << "b = " << b << endl;
    cout << "*b = " << *b << endl;
    
    delete[] a;
}