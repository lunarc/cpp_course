#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
    for (auto i=99999999; i<100000000; i++)
        cout << i << ", " << typeid(i).name() << endl;
}
