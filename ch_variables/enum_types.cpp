#include <iostream>

using namespace std;

int main() 
{
    enum { RED, GREEN, BLUE, YELLOW };
    
    cout << "RED = " << RED << endl;
    cout << "GREEN = " << GREEN << endl;
    cout << "BLUE = " << BLUE << endl;
    cout << "YELLOW = " << YELLOW << endl;
    
    enum flavor { VANILLA, CHOCOLATE, ORANGE, STRAWBERRY };
    
    flavor selectedFlavor = ORANGE;
    
    cout << "selectedFlavor = " << selectedFlavor << endl;
    
    enum status { FINISHED = 0, ERROR = 15 };
    
    status currentStatus = ERROR;
    
    cout << "currentStatus = " << currentStatus << endl;
}