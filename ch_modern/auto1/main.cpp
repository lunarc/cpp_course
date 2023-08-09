#include <iostream>
#include <typeinfo>

using namespace std;

class MyClass {
};

int main()
{
    auto i = 42;
    auto j = 42L;
    
    cout << "sizeof(i) = " << sizeof(i) << endl;
    cout << "sizeof(j) = " << sizeof(j) << endl;
    
    auto c = new MyClass();
    
    cout << "c is a " << typeid(c).name() << endl;
    
    for (auto k=0; k<5; k++)
        cout << k << endl;
    
}
    
    