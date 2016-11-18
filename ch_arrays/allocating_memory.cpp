#include <iostream>

using namespace std;

int main()
{
    int* a = 0;
    
    a = new int;
    
    *a = 42;
    
    cout << "a = " << a << endl;
    cout << "*a = " << *a << endl;
    
    delete a;
}