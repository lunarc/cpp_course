#include <iostream>
#include <memory>

using namespace std;

int main()
{
    shared_ptr<int[]> a(new int[10]);
    shared_ptr<int[]> b = a;
    
    for (int i=0; i<10; i++)
        a[i] = i;
     
    cout << "a.get() = " << a.get() << endl;
    cout << "a[5] = " << a[5] << endl;
    cout << "b.get() = " << b.get() << endl;
    cout << "*b = " << *(b.get()) << endl;
}