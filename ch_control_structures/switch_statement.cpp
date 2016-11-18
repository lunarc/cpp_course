#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    enum colorType { RED, GREEN, BLUE, YELLOW, ORANGE };
    srand((unsigned)time(0));
    
    
    for (int i=0; i<4; i++)
    {
        colorType color = colorType(rand()%5);
        switch (color)
        {
            case RED:
                cout << "Color is red." << endl;
                break;
            case GREEN:
                cout << "Color is green." << endl;
                break;
            default:
                cout << "Color is either BLUE, YELLOW or ORANGE." << endl;
                break;
        }
    }
}