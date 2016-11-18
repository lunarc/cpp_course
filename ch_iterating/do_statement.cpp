#include <iostream>

using namespace std;

int main() 
{
    int counter = 1;
    
    do
    {
        cout << "counter = " << counter << endl;
        counter = counter + 1;
    }
    while (counter<=10);
}