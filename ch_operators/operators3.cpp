#include <iostream>

using namespace std;

int main()
{
    int number;
    
    cout << "Enter a number : ";
    
    cin >> number;
    
    int outValue = (number>50) ? 42 : 21;
    
    cout << "outValue = " << outValue;
}