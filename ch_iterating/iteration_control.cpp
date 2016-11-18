#include <iostream>

using namespace std;

int main() 
{
    int counter = 1;
    
    while (counter <= 10) 
    {
        cout << "counter = " << counter << endl;
        
        if (counter == 5)
        {
            counter = counter + 2;
            continue;
        }
        
        if (counter == 9)
            break;
        
        counter = counter + 1;
    }
}