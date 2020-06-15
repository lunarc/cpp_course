#include <iostream>

using namespace std;

int main()
{
    auto sum = 0;
    
    for (auto i=0; i<=10000; sum += ++i);
    
    cout << "sum = " << sum << endl;
}
