#include <iostream>

using namespace std;

int main()
{
    int* a = nullptr;
    
    a = new int;
    
    *a = 42;
    
    cout << "a = " << a << endl;
    cout << "*a = " << *a << endl;
    
    delete a;
}
