#include <iostream>
#include <memory>

using namespace std;

int main()
{
    unique_ptr<int> a(new int);
    
    *a = 42;
    
    cout << "a.get() = " << a.get() << endl;
    cout << "*a = " << *(a.get()) << endl;
}