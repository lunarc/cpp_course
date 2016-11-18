#include <iostream>

using namespace std;

int main()
{
    int sum = 0;
    
    for (int i=0; i<=10000; sum += ++i);
    
    cout << "sum = " << sum << endl;
}
