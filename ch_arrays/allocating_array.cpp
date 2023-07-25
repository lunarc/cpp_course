#include <iostream>

using namespace std;

int main()
{
    int* a = nullptr;
    int* b = nullptr;
    
    a = new int[10];
    
    for (auto i=0; i<10; i++)
        a[i] = i;
    
    b = &a[6];
    
    cout << "a = " << a << endl;
    cout << "a[5] = " << a[5] << endl;
    cout << "b = " << b << endl;
    cout << "*b = " << *b << endl;
    
    delete[] a;
}
