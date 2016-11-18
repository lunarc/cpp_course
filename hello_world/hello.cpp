#include <iostream>

using namespace std;

int main()
{
    int sum, i;
    
    for (sum=0, i=0;i<100;sum+=i,i++);
    cout << "sum = " << sum << endl;
    for (sum=0, i=0;i<100;i++,sum+=i);
    cout << "sum = " << sum << endl;
    
    cout << "Hello, C++" << endl;
}