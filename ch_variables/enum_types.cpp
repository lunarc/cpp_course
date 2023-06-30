#include <iostream>

using namespace std;

int main()
{
    enum
    {
        Red,
        Green,
        Blue,
        Yellow
    };

    cout << "RED = " << Red << endl;
    cout << "GREEN = " << Green << endl;
    cout << "BLUE = " << Blue << endl;
    cout << "YELLOW = " << Yellow << endl;

    enum flavor
    {
        Vanilla,
        Chocolate,
        Orange,
        Strawberry
    };

    flavor selectedFlavor = Orange;

    cout << "selectedFlavor = " << selectedFlavor << endl;

    enum status
    {
        Finished = 0,
        Error = 15
    };

    status currentStatus = Error;

    cout << "currentStatus = " << currentStatus << endl;

    enum class Color
    {
        Grey,
        Cyan,
        Purple
    };

    Color color = Color::Cyan;
}
