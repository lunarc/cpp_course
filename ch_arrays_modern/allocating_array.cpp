#include <iostream>

using namespace std;

int main()
{
    std::shared_ptr<int[]> a(new int[10]);
    std::shared_ptr<int[]> b = a;
    
    for (int i=0; i<10; i++)
        a[i] = i;
     
    cout << "a = " << a << endl;
    cout << "a[5] = " << a[5] << endl;
    cout << "b = " << b << endl;
    cout << "*b = " << *(b.get()) << endl;
}