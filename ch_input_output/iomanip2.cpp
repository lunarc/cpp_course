#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    bool flag = true;
    
    cout << "flag = " << flag << endl;
    cout << boolalpha;
    cout << "flag = " << flag << endl;

    int n = 42;
    
    cout << hex << "n = " << n << endl;
    cout << hex << showbase << "n = " << n << endl;
    cout << oct << "n = " << n << endl;
    cout << dec << "n = " << n << endl;
}