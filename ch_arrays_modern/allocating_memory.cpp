#include <iostream>

using namespace std;

int main()
{
    unique_ptr<int> a(new int);
    
    *a = 42;
    
    cout << "a = " << a << endl;
    cout << "*a = " << *a << endl;
}