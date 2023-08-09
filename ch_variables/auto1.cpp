#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
    auto a = 42;    // By default int
    auto b = 42l;   // suffix defines a long
    auto c = 42.0;  // By default a double
    auto d = 42.0f; // suffix denotes a float

    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    cout << typeid(d).name() << endl;
}
