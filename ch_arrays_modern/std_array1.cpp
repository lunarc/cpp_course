#include <iostream>
#include <array>

using namespace std;

int main()
{
    array<int, 10> a;
    
    for (int i=0; i<10; i++)
        a[i] = i;

    for (auto v : a)
        cout << v << endl;
     
    cout << "a.data() = " << a.data() << endl;
    cout << "a[5] = " << a[5] << endl;
}